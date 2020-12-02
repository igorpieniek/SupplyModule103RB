/*
 * Tools.h
 *
 *  Created on: 23.04.2018
 *      Author: mice
 */

#ifndef CLASSES_TOOLS_H_
#define CLASSES_TOOLS_H_

#include "stdint.h"

extern class Tools {

	uint8_t MicrosInitDone = 0;
public:

	uint8_t Init(void);
	uint8_t GetMicrosState(void);
	uint32_t GetMicros(void);
	int32_t CompareMicros(uint32_t a, uint32_t b);

	Tools();
	virtual ~Tools();
}tools;

#endif /* CLASSES_TOOLS_H_ */
