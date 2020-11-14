/*
 * Fun.h
 *
 *  Created on: 14.11.2020
 *      Author: Igor
 */

#ifndef INC_FUN_H_
#define INC_FUN_H_

#include "main.h"



class Fun {
public:
	enum Velocity{
		ZERO,
		LOW,
		NORMAL,
		HIGH
	};

	void on(Velocity vel= NORMAL);
	void off();
	uint8_t isOn();
	float getPWMvalue();

	Fun(TIM_HandleTypeDef * tim, uint32_t ch);
	virtual ~Fun();
private:

	uint8_t is_on;
	TIM_HandleTypeDef * timer;
	uint32_t channel;

};

#endif /* INC_FUN_H_ */
