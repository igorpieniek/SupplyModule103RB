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

class RtosTool{
public:
	RtosTool();
    void registerQueue(BaseRtosMsg::MsgType type, uint8_t queueSize);
    void insertData(BaseRtosMsg::MsgType type, BaseRtosMsg& data);
    BaseRtosMsg* pop(BaseRtosMsg::MsgType type);

private:


};

#endif /* INC_RTOSTOOL_H_ */
