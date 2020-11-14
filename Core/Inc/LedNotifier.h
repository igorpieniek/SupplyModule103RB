/*
 * LedNotifier.h
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#ifndef INC_LEDNOTIFIER_H_
#define INC_LEDNOTIFIER_H_

#include "main.h"


class LedNotifier {
private:
	GPIO_TypeDef *GPIOx;
	uint16_t GPIO_Pin;

	enum LedState{
		OFF=0,
		ON,
		BLINK
	};

	LedState curState;
	uint16_t blinkPeriodON, blinkPeriodOFF;

	uint8_t isReversed;
	GPIO_PinState onState; //state consider as ON
	GPIO_PinState getONPinState(){ return onState;};
	GPIO_PinState getOFFPinState(){return !onState; };

public:
	void on();
	void off();
	void blink( uint16_t perON);
	void blink( uint16_t perON, uint16_t perOFF);

	LedState getState();

	LedNotifier(GPIO_TypeDef port, uint16_t pin, uint8_t rev=0);
	virtual ~LedNotifier();
};

#endif /* INC_LEDNOTIFIER_H_ */
