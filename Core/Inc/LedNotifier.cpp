/*
 * LedNotifier.cpp
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#include <LedNotifier.h>

LedNotifier::LedNotifier(GPIO_TypeDef port, uint16_t pin,uint8_t rev) {

	if(rev) onState = GPIO_PIN_RESET;
	else    onState = GPIO_PIN_SET;
}

LedNotifier::~LedNotifier() {
	// TODO Auto-generated destructor stub
}

