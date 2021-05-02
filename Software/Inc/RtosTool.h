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
#include <vector>
#include <unordered_map>

class RtosTool{
public:
	RtosTool();

    template<typename MsgClass>
	void registerQueue(uint8_t queueSize);

    template<typename MsgClass>
    void insertData(MsgClass& data);

    template<typename MsgClass>
    MsgClass* pop(BaseRtosMsg::MsgType type); // bedzie mozna uzyć MsgClass.getMsgType

private:
    struct QueuePools{
    	osPoolId mpool;
    	osMessageQId  msgBox;
    };
    std::unordered_map<BaseRtosMsg::MsgType, QueuePools> queuesData;

};

#endif /* INC_RTOSTOOL_H_ */
