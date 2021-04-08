/*
 * Fan.h
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#ifndef INC_FAN_H_
#define INC_FAN_H_

#include "main.h"


/** Class to define functions typical for Fans.
 * User can turn on fan and choose velocity (typical or custom)
 *  */
class Fan {
public:
	/** Velocity levels available to set */
	enum Velocity{
		ZERO,			/**< Zero speed- it's  OFF*/
		LOW = 300, 		/**< Low speed : 30% */
		NORMAL = 650,	/**< Normal speed : 65% */
		HIGH= 1000		/**< Max speed : 100% */
	};

	/** Turn ON Fan
	 * @param vel - Velocity (optional) - normally velocity is set to NORMAL() */
	void on(Velocity vel= NORMAL);

	/**Turn ON Fan - with custom speed in range <ZERO(), HIGH()>
	 * @param vel - uint16_t - custom value of speed*/
	void on(uint16_t vel);

	/**Turn off Fan */
	void off();

	/** Return info about current state of Fan*/
	uint8_t isOn()const{ return is_on;};

	/** Return current PWM value in percents [%]*/
	float getPWMvalue();

	/**
	 * @param tim - TIM_HandleTypeDef * - to define timer to use eg. htim12
	 * @param ch - uint32_t - timer channel eg. TIM_CHANNEL_1
	 */
	void init(TIM_HandleTypeDef * tim, uint32_t ch);
	Fan();
	virtual ~Fan();
private:

	uint8_t is_on;
	TIM_HandleTypeDef * timer;

	uint32_t channel;
	uint16_t velocity;

	void stateOFF(){is_on = 0;};
	void stateON() {is_on = 1;};

	/** Start timer and set compare value
	 * @param compare_val - value to be write in timer CCR register */
	void timerSTART(uint16_t compare_val);

};

#endif /* INC_FAN_H_ */
