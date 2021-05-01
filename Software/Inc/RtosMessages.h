/*
 * RtosMessages.h
 *
 *  Created on: 1 maj 2021
 *      Author: Igor
 */

#ifndef INC_RTOSMESSAGES_H_
#define INC_RTOSMESSAGES_H_


#include "main.h"


class BaseRtosMsg{
public:
    enum  MsgType{
        DATA1,
		DATA2,
        TEMPERATURE,
        BRANCH_DATA,
        FAN1
    };
    BaseRtosMsg(MsgType mt): mtype(mt){};
private:
    MsgType mtype;
};

class Data1: BaseRtosMsg{
	Data1(): BaseRtosMsg(DATA1){};
    uint8_t x;
    uint8_t y;
    uint16_t z;
};

class Data2: BaseRtosMsg{
	Data2(): BaseRtosMsg(DATA2){};
    uint8_t xx;
    uint8_t yy;
    uint16_t zz;
};




#endif /* INC_RTOSMESSAGES_H_ */
