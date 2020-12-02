/*
 * Tools.cpp
 *
 *  Created on: 23.04.2018
 *      Author: mice
 */

#include <Tools.h>


Tools tools;

uint8_t Tools::getMicrosState(void){
	return microsInitDone;
}
uint32_t Tools::getMicros(void){
	return TOOL_TIMER.Instance->CNT;
}
int32_t Tools::compareMicros(uint32_t a, uint32_t b) {
	return (int32_t)(a - b);
}
void Tools::init(void) {
	if (!microsInitDone) {
		HAL_TIM_Base_Start(&TOOL_TIMER);
		microsInitDone = 1;
	}
}


Tools::Tools(): microsInitDone(0) {
	// TODO Auto-generated constructor stub

}

Tools::~Tools() {
	// TODO Auto-generated destructor stub
}

