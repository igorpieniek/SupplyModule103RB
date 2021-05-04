/*
 * RtosTool.h
 *
 *  Created on: 1 maj 2021
 *      Author: Igor
 */

#ifndef INC_RTOSTOOL_H_
#define INC_RTOSTOOL_H_


#include "main.h"
#include "RtosMessages.h"
#include "cmsis_os.h"
#include <unordered_map>
#include <cstring>


/** FreeRTOS tool.
 * Class to help with adding queues and manage adding and receiving messages from a queue
 *
 * There are 2 steps to start using class (creating RtosTool instance not included):
 * 1. Add your data structure in RtosMessages.h. You have to use BaseRtosMsg as base!
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 * struct Data1: BaseRtosMsg{
 *		Data1(): BaseRtosMsg( UniqueID::getUniqueID<Data1>() ){};
 * 		uint8_t x;
 *		uint8_t y;
 * };
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * 2. Register your struct using type and queue size in the same place
 * where you define your threads:
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 * tool.registerQueue<Data1>(5);
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Putting data into queue:
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 * Data1 data;
 * data.x =9;
 * data.y =8;
 * data.z = 7;
 * tool.insert<Data1>(data);
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * Getting data from queue:
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 * Data1 dataToFill;
 * uint8_t isReceived = tool.pop<Data1>(&data);
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 *	When you use pop method you could define timeout, default timeout is 0 and that mean
 *	the function returns instantly.
 */

class RtosTool{
public:

    template<typename MsgClass>
	void registerQueue(uint8_t queueSize);

    template<typename MsgClass>
    void insert(MsgClass& data);

    /* Fill data structure passed in first argument and return bool value: true when there was
     * something pending in queue or false if there wasn't any messages in queue */
    template<typename MsgClass>
    uint8_t pop(MsgClass* data, uint32_t timeout = {0});

private:
    struct QueuePools{
    	osPoolId mpool;
    	osMessageQId  msgBox;
    };
    std::unordered_map<uint16_t, QueuePools> queuesData;

};



template<class MsgClass>
void RtosTool::registerQueue(uint8_t queueSize) {

	const osPoolDef_t os_pool_defx = { queueSize, sizeof(MsgClass), NULL };
	const osMessageQDef_t os_messageQ_defx ={ queueSize, sizeof(MsgClass), NULL, NULL };

	QueuePools queuePools;
	queuePools.mpool  = osPoolCreate(&os_pool_defx);
	queuePools.msgBox = osMessageCreate(&os_messageQ_defx, NULL);

	MsgClass obj;
	uint16_t msgId = obj.getMsgID();

	queuesData.insert(std::pair<uint16_t, QueuePools>(msgId, queuePools));
}




template<typename MsgClass>
void RtosTool::insert(MsgClass& data) {

	QueuePools  queuePools = queuesData[data.getMsgID()];

	MsgClass* mptr = (MsgClass*)osPoolAlloc(queuePools.mpool);
	std::memcpy(mptr, &data, sizeof(MsgClass));
	osMessagePut(queuePools.msgBox, (uint32_t)mptr, osWaitForever);

}
template<typename MsgClass>
uint8_t RtosTool::pop(MsgClass* data, uint32_t timeout) {
	osEvent  evt;
	QueuePools  queuePools = queuesData[data->getMsgID()];

    evt = osMessageGet(queuePools.msgBox, timeout);
    if (evt.status == osEventMessage) {
    	std::memcpy(data, evt.value.p, sizeof(MsgClass));
    	osPoolFree(queuePools.mpool, evt.value.p);
    	return 1;
    }
    else{ //e.g. osEventTimeout
    	return 0;
    }
}

#endif /* INC_RTOSTOOL_H_ */
