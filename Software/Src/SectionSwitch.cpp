/*
 * SectionSwitch.cpp
 *
 *  Created on: 18.11.2020
 *      Author: Igor
 */

#include <SectionSwitch.h>

SectionSwitch::SectionSwitch(GPIO_TypeDef * por, uint16_t pi, GPIO_PinState state):
							port(por), pin(pi){
	// TODO Auto-generated constructor stub
	HAL_GPIO_WritePin(port, pin, state);
	if (state == GPIO_PIN_SET) realState = ON;
	else 					   realState = OFF;
}

SectionSwitch::~SectionSwitch() {
	// TODO Auto-generated destructor stub
}

void SectionSwitch::on(){
	realState = ON;
	HAL_GPIO_WritePin(port,pin, GPIO_PIN_SET );
}

void SectionSwitch::off(){
	realState = OFF;
	HAL_GPIO_WritePin(port,pin, GPIO_PIN_RESET );
}

void SectionSwitch::updateRealStateON(){
	realState = ON_BY_SLIDER;
}
