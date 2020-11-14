/*
 * Fun.cpp
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#include <Fun.h>

void Fun::on(Velocity vel){
	velocity = vel;
	HAL_TIM_Base_Start(timer);
	HAL_TIM_PWM_Start(timer, channel);
	 __HAL_TIM_SET_COMPARE(timer, channel, vel);

}

void Fun::on(uint16_t vel){
	if(vel> HIGH ) vel = HIGH;
	else if (vel < 0) vel = ZERO;
	velocity = vel;
	HAL_TIM_Base_Start(timer);
	HAL_TIM_PWM_Start(timer, channel);
	 __HAL_TIM_SET_COMPARE(timer, channel, vel);

}

void Fun::off(){
	HAL_TIM_PWM_Stop(timer, channel);
	 __HAL_TIM_SET_COMPARE(timer, channel, ZERO);

}

uint8_t Fun::isOn()const { return is_on;}

float Fun::getPWMvalue(){
	return 100*(float)velocity / (float)HIGH;
}



Fun::Fun(TIM_HandleTypeDef * tim, uint32_t ch):
	timer(tim), channel(ch), is_on(0){


}

Fun::~Fun() {
	// TODO Auto-generated destructor stub
}

