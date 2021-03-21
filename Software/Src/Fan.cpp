/*
 * Fan.cpp
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#include <Fan.h>

Fan::Fan(void) {}

void Fan::init(TIM_HandleTypeDef *tim, uint32_t ch) {
	timer = tim;
	channel = ch;
	is_on = 0;
}

void Fan::on(Velocity vel){
	velocity = vel;
	stateON();
	timerSTART((uint16_t) vel);
}

void Fan::on(uint16_t vel){
	if(vel> HIGH ) vel = HIGH;
	else if (vel < 0) vel = ZERO;
	velocity = vel;
	stateON();
	timerSTART(vel);
}



void Fan::timerSTART(uint16_t compare_val){
	HAL_TIM_Base_Start(timer);
	HAL_TIM_PWM_Start(timer, channel);
	__HAL_TIM_SET_COMPARE(timer, channel, compare_val);
}

void Fan::off(){
	stateOFF();
	HAL_TIM_PWM_Stop(timer, channel);
	 __HAL_TIM_SET_COMPARE(timer, channel, ZERO);

}

float Fan::getPWMvalue(){
	return 100*(float)velocity / (float)HIGH;
}


Fan::~Fan() {
	// TODO Auto-generated destructor stub
}


