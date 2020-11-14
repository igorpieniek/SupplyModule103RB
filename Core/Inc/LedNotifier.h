/*
 * LedNotifier.h
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#ifndef INC_LEDNOTIFIER_H_
#define INC_LEDNOTIFIER_H_

#include "main.h"
#include "cmsis_os.h"


class LedNotifier {
public:
	void on();
	void off();
	void blink( uint32_t perON);
	void blink( uint32_t perON, uint32_t perOFF);
	void toggle();

	enum LedState{
		OFF=0,
		ON,
		BLINK
	};

	LedState getState();
	uint32_t getPeriod();

	void process();


	LedNotifier(GPIO_TypeDef *port, uint16_t pin, uint8_t rev=0);
	virtual ~LedNotifier();
private:
	GPIO_TypeDef *Port;
	uint16_t Pin;

	LedState curState;
	uint32_t blinkPeriodON, blinkPeriodOFF, currPeriod;

	uint8_t isReversed;
	GPIO_PinState onState; //state consider as ON
	GPIO_PinState offState; //state consider as OFF
	GPIO_PinState getONPinState(){ return onState;};
	GPIO_PinState getOFFPinState(){return offState; };


};

#endif /* INC_LEDNOTIFIER_H_ */
