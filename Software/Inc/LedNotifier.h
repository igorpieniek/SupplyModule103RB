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
#include "TimeTool.h"

/** Tool intended for led's, it provide typical behaviours for notifier - ON/OFF or blink.
 * To blink mechanism it use TimeTool() global class object to calculate time between toggles.
 * To blink use blink() functions. blink_process() could be used only by manager task.
 *
 * Led blinking could be stopped by using on() / off() method
 */
class LedNotifier {
public:

	void on();
	void off();

	void blink( uint16_t milisOnOff);
	void blink( uint16_t milisOn, uint16_t milisOff);

	/** Function that should be called by task process only - it toggle LED in right time. It work only when
	 *  blink() function was used before. Without this operation nothing will happen.*/
	void blink_process();

	/** Enum to specify state of lednotifier object */
	enum LedState{
		OFF,
		ON,
		BLINK
	};

	LedState getState();

	/**
	 * @param rev - uint8_t flag (optional) normally 0, but it should be set as 1 if there is reversed logic -
	 *  eg. high state on pin -> led is turn off
	 */
	LedNotifier(GPIO_TypeDef *port, uint16_t pin, uint8_t rev= 0);
	virtual ~LedNotifier();
private:
	GPIO_TypeDef *Port;
	uint16_t Pin;

	uint16_t blinkPeriodON, blinkPeriodOFF; /** blinking periods */
	uint16_t last_toggle_time;

	enum BlinkState{
		blinkOff, blinkOn
	}blink_state;

	LedState curState;

	uint8_t isReversed;   								/** flag of reversed led logic */
	GPIO_PinState onState; 								/** state consider as ON */
	GPIO_PinState offState; 							/** state consider as OFF */
	GPIO_PinState getONPinState(){ return onState;};  	/** return real ON state */
	GPIO_PinState getOFFPinState(){return offState; }; 	/** return real OFF state */

	// Additional function need in blinking process
	uint32_t getPeriod();		/** return current period in blinking process: blinkPeriodON / blinkPeriodOFF */
	void toggle_blinkstate();	/** toggle current blink_state (enum BlinkState) */
	void toggle();				/** toggle led pin state */

	uint16_t getTimeFromLastToggle(); 	/** compare saved CNT state, and current CNT state and return the difference [ms] */
	void updateLastToggleTime();		/** reset saved CNT state by saving current state of counter */


};

#endif /* INC_LEDNOTIFIER_H_ */
