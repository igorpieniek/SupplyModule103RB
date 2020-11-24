/*
 * Fun.h
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#ifndef INC_FUN_H_
#define INC_FUN_H_

#include "main.h"


/** Class to define functions typical for Fun.
 * User can turn on fun and choose velocity (typical or custom)
 *  */
class Fun {
public:
	/** Velocity levels available to set */
	enum Velocity{
		ZERO,			/**< Zero speed. Fun if turn OFF*/
		LOW = 300, 		/**< Low speed : 30% */
		NORMAL = 650,	/**< Normal speed : 65% */
		HIGH= 1000		/**< Max speed : 100% */
	};

	/** Turn ON Fun
	 * @param vel - Velocity (optional) - normally velocity is set to NORMAL() */
	void on(Velocity vel= NORMAL);

	/**Turn ON Fun - with custom speed in range <ZERO(), HIGH()>
	 * @param vel - uint16_t - custom value of Fun speed*/
	void on(uint16_t vel);

	/**Turn off Fun */
	void off();

	/** Return info about current state of Fun*/
	uint8_t isOn()const{ return is_on;};

	/** Return current PWM value in percents [%]*/
	float getPWMvalue();

	/**
	 * @param tim - TIM_HandleTypeDef * - to define timer to use
	 * @param ch - uint32_t - timer channel
	 */
	Fun(TIM_HandleTypeDef * tim, uint32_t ch);
	virtual ~Fun();
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

#endif /* INC_FUN_H_ */
