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
 * There are 3 steps to start using class (creating RtosTool instance not included):
 */

class RtosTool{
public:
	RtosTool();

    template<typename MsgClass>
	void registerQueue(uint8_t queueSize);

    template<typename MsgClass>
    void insert(MsgClass& data);

    /* Fill data structure passed in first argument and return bool value: true when there was
     * something pending in queue or false if there wasn't any messages in queue */
    template<typename MsgClass>
    uint8_t pop(MsgClass& data, uint32_t timeout = {0});

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

	MsgClass* mptr = osPoolAlloc(queuePools.mpool);
	std::memcpy(mptr, &data, sizeof(MsgClass));
	osMessagePut(queuePools.msgBox, (uint32_t)mptr, osWaitForever);

}
template<typename MsgClass>
uint8_t RtosTool::pop(MsgClass& data, uint32_t timeout) {
	osEvent  evt;
	QueuePools  queuePools = queuesData[data.getMsgID()];

    evt = osMessageGet(queuePools.msgBox, timeout);
    if (evt.status == osEventMessage) {
    	std::memcpy(&data, evt.value.p, sizeof(MsgClass));
    	osPoolFree(queuePools.mpool, evt.value.p);
    	return 1;
    }
    else{ //e.g. osEventTimeout
    	return 0;
    }
}

#endif /* INC_RTOSTOOL_H_ */
