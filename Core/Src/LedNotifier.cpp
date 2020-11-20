/*
 * LedNotifier.cpp
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#include <LedNotifier.h>

void LedNotifier::on(){
	if(curState == BLINK) timerSTOP();
	curState = ON;
	HAL_GPIO_WritePin(Port,Pin, getONPinState());

}
void LedNotifier::off(){
	if(curState == BLINK) timerSTOP();
	curState = OFF;
	HAL_GPIO_WritePin(Port,Pin, getOFFPinState());

}

void LedNotifier::toggle(){
	HAL_GPIO_TogglePin(Port,Pin);
	if (blink_state == blinkOff) blink_state = blinkOn;
	else 						 blink_state = blinkOff;
}

uint32_t LedNotifier::getPeriod(){
	if(blink_state == blinkOff) return blinkPeriodOFF;
	else 						return blinkPeriodON;
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
	blink_state = blinkOn;

//	timer->Instance->ARR =perON;
	__HAL_TIM_SET_AUTORELOAD(timer, perON);
	HAL_TIM_Base_Start_IT(timer);
	HAL_GPIO_WritePin(Port,Pin, getONPinState());

}
void LedNotifier::blink_process(){
	// process called by timer interrupt (not directly)
	if(curState == BLINK){

		timerSTOP();
		toggle();
//		timer->Instance->ARR = getPeriod();
		__HAL_TIM_SET_AUTORELOAD(timer, getPeriod());
		HAL_TIM_Base_Start_IT(timer);


	}
}

void LedNotifier::timerSTOP(){
	HAL_TIM_Base_Stop_IT(timer);
	__HAL_TIM_SetCounter(timer, 0 );
}

LedNotifier::LedState LedNotifier::getState(){
	return curState;
}


LedNotifier::LedNotifier(GPIO_TypeDef *port, uint16_t pin,TIM_HandleTypeDef* tim,uint8_t rev):
	Port(port), Pin(pin), timer(tim){
	isReversed = rev;
	if(isReversed){ onState = GPIO_PIN_RESET; offState= GPIO_PIN_SET;}
	else    {onState = GPIO_PIN_SET;   offState= GPIO_PIN_RESET;}

}

LedNotifier::~LedNotifier() {
	// TODO Auto-generated destructor stub
}

