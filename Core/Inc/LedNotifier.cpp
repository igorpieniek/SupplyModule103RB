/*
 * LedNotifier.cpp
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#include <LedNotifier.h>

void LedNotifier::on(){
	HAL_GPIO_WritePin(Port,Pin, getONPinState());
}
void LedNotifier::off(){

}
void LedNotifier::blink( uint16_t perON){

}
void LedNotifier::blink( uint16_t perON, uint16_t perOFF){

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

