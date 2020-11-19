/*
 * LedNotifier.cpp
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#include <LedNotifier.h>

void LedNotifier::on(){
	HAL_GPIO_WritePin(Port,Pin, getONPinState());
	curState = ON;
}
void LedNotifier::off(){
	HAL_GPIO_WritePin(Port,Pin, getOFFPinState());
	curState = OFF;
}

void LedNotifier::toggle(){
	HAL_GPIO_TogglePin(Port,Pin);
}

uint32_t LedNotifier::getPeriod(){
	if (currPeriod == blinkPeriodON) currPeriod = blinkPeriodOFF;
	else currPeriod = blinkPeriodON;
	return currPeriod;
}
void LedNotifier::blink_config( uint32_t perON){
	blink_config(perON,perON);
}

void LedNotifier::blink_config( uint32_t perON, uint32_t perOFF){
	off();
	curState = BLINK;
	blinkPeriodON = perON;
	blinkPeriodOFF = perOFF;
	currPeriod = perOFF;

	timer.Instance->ARR =perON;
	HAL_TIM_Base_Start_IT(&timer);

}
void LedNotifier::blink_process(){
	// process called by timer interrupt (not directly)
	if(curState == BLINK){
		HAL_TIM_Base_Stop_IT(&timer);
		__HAL_TIM_SetCounter(&timer, 0 );

		toggle();
		timer.Instance->ARR = getPeriod();
		HAL_TIM_Base_Start_IT(&timer);

	}
}

LedNotifier::LedState LedNotifier::getState(){
	return curState;
}


LedNotifier::LedNotifier(GPIO_TypeDef *port, uint16_t pin,TIM_HandleTypeDef tim,uint8_t rev):
	Port(port), Pin(pin), timer(tim){
	isReversed = rev;
	if(isReversed){ onState = GPIO_PIN_RESET; offState= GPIO_PIN_SET;}
	else    {onState = GPIO_PIN_SET;   offState= GPIO_PIN_RESET;}

}

LedNotifier::~LedNotifier() {
	// TODO Auto-generated destructor stub
}

