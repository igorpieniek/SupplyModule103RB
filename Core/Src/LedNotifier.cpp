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
void LedNotifier::blink( uint32_t perON){
	blink(perON,perON);
}

void LedNotifier::blink( uint32_t perON, uint32_t perOFF){
	off();
	curState = BLINK;
	blinkPeriodON = perON;
	blinkPeriodOFF = perOFF;
	currPeriod = perOFF;
}
LedNotifier::LedState LedNotifier::getState(){
	return curState;
}

void LedNotifier::process(){
	if(getState() == LedNotifier::BLINK){
		toggle();
		osDelay(getPeriod());

	}
}

LedNotifier::LedNotifier(GPIO_TypeDef *port, uint16_t pin,uint8_t rev) {
	isReversed = rev;
	if(isReversed){ onState = GPIO_PIN_RESET; offState= GPIO_PIN_SET;}
	else    {onState = GPIO_PIN_SET;   offState= GPIO_PIN_RESET;}

	Port = port;
	Pin = pin;

}

LedNotifier::~LedNotifier() {
	// TODO Auto-generated destructor stub
}

