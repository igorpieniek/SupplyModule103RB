/*
 * RtosMessages.h
 *
 *  Created on: 1 maj 2021
 *      Author: Igor
 */

#ifndef INC_RTOSMESSAGES_H_
#define INC_RTOSMESSAGES_H_


#include "main.h"




//--------------------------BASE STRUCT TOOLS--------------------------------------------------

namespace UniqueID{
	uint16_t idCount = 0;

	template <typename T>
	uint16_t getUniqueID()
	{
		static uint16_t id = idCount++;
		return id;
	}
};


class BaseRtosMsg{
public:

    BaseRtosMsg(uint16_t uniqueID): id(uniqueID){};

    uint16_t getMsgID()const { return id;};
private:
    const uint16_t id;
};


//--------------------------MESSAGES STRUCTS--------------------------------------------------
struct Data1: BaseRtosMsg{
	Data1(): BaseRtosMsg( UniqueID::getUniqueID<Data1>() ){};
    uint8_t x;
    uint8_t y;
    uint16_t z;
};

struct Data2: BaseRtosMsg{
	Data2(): BaseRtosMsg( UniqueID::getUniqueID<Data2>() ){};
    uint8_t xx;
    uint8_t yy;
    uint16_t zz;
};





#endif /* INC_RTOSMESSAGES_H_ */
