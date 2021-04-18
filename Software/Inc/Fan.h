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
		LOW    = 300,   /**< Low speed : 30% */
		NORMAL = 650,	/**< Normal speed : 65% */
		HIGH   = 1000   /**< Max speed : 100% */
	};


	void on(Velocity vel= NORMAL);
	void on(uint16_t vel);
	void off();
	uint8_t isOn()const{ return is_on;};

	float getPWMvalue();

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
