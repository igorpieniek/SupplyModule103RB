/*
 * Tools.cpp
 *
 *  Created on: 23.04.2018
 *      Author: mice
 */

#include <Tools.h>
#include "tim.h"

Tools tools;

uint8_t Tools::GetMicrosState(void){
	return MicrosInitDone;
}
uint32_t Tools::GetMicros(void){
	return TIM5->CNT;
}
int32_t Tools::CompareMicros(uint32_t a, uint32_t b) {
	return (int32_t)(a - b);
}
uint8_t Tools::Init(void) {
	if (MicrosInitDone) {
		return 0;
	} else {
		MX_TIM5_Init();
		HAL_TIM_Base_Start(&htim5);
		MicrosInitDone = 1;

	}
	return 1;
}


Tools::Tools() {
	// TODO Auto-generated constructor stub

}

Tools::~Tools() {
	// TODO Auto-generated destructor stub
}

