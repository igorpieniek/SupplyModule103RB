/*
 * LedNotifier.h
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#ifndef INC_LEDNOTIFIER_H_
#define INC_LEDNOTIFIER_H_

#include "main.h"
#include "gpio.h"
#include "tim.h"

/*
 * To correctly define object of this class you have to define
 * one timer in OnePulse mode.
 * To make led blink first you had to define use blink_config to determine
 * periods. Next blink_process has to be called by interrupt function: PeriodElapsed.
 * It should call blink_process directly or by osSignal method
 */
class LedNotifier {
public:
	void on();
	void off();
	void blink_config( uint32_t perON);
	void blink_config( uint32_t perON, uint32_t perOFF);
	void blink_process();


	enum LedState{
		OFF=0,
		ON,
		BLINK
	};

	LedState getState();

	LedNotifier(GPIO_TypeDef *port, uint16_t pin,TIM_HandleTypeDef* tim, uint8_t rev=0);
	virtual ~LedNotifier();
private:
	GPIO_TypeDef *Port;
	uint16_t Pin;
	TIM_HandleTypeDef* timer;

	uint32_t blinkPeriodON, blinkPeriodOFF; // blinking periods

	enum BlinkState{
		blinkOff, blinkOn
	}blink_state;
	LedState curState;

	uint8_t isReversed;
	GPIO_PinState onState; //state consider as ON
	GPIO_PinState offState; //state consider as OFF
	GPIO_PinState getONPinState(){ return onState;};
	GPIO_PinState getOFFPinState(){return offState; };

	uint32_t getPeriod();
	void timerSTOP();
	void timerSTART();
	void toggle_blinkstate();
	void toggle();


};

#endif /* INC_LEDNOTIFIER_H_ */
