/*
 * SectionSwitch.cpp
 *
 *  Created on: 18.11.2020
 *      Author: Igor
 */

#include <SectionSwitch.h>

SectionSwitch::SectionSwitch(GPIO_TypeDef * por, uint16_t pi, GPIO_PinState st):
							port(por), pin(pi), state(st){
	// TODO Auto-generated constructor stub
	HAL_GPIO_WritePin(port, pin, state);
	if (state == GPIO_PIN_SET) realState = ON;
	else 					   realState = OFF;
}

SectionSwitch::~SectionSwitch() {
	// TODO Auto-generated destructor stub
}

