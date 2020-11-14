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
		LOW = 300,
		NORMAL = 650,
		HIGH= 1000
	};

	void on(Velocity vel= NORMAL);
	void on(uint16_t vel);
	void off();
	uint8_t isOn()const;
	float getPWMvalue();

	Fun(TIM_HandleTypeDef * tim, uint32_t ch);
	virtual ~Fun();
private:

	uint8_t is_on;
	TIM_HandleTypeDef * timer;
	uint32_t channel;
	uint16_t velocity;

};

#endif /* INC_FUN_H_ */
