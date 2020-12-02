/*
 * Tools.h
 *
 *  Created on: 23.04.2018
 *      Author: mice
 */

#ifndef CLASSES_TOOLS_H_
#define CLASSES_TOOLS_H_

#include "stdint.h"
#include "tim.h"

#define TOOL_TIMER htim4

extern class Tools {

	uint8_t microsInitDone;
public:

	void init(void);
	uint8_t getMicrosState(void);
	uint32_t getMicros(void);
	int32_t compareMicros(uint32_t a, uint32_t b);

	Tools();
	virtual ~Tools();
}tools;


#endif /* CLASSES_TOOLS_H_ */
