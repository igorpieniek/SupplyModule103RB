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
		Off=0,
		On,
		BLINK
	};

	LedState curState;
	uint16_t blinkPeriodON, blinkPeriodOFF;
public:
	void ON();
	void OFF();
	void blink( uint16_t perON);
	void blink( uint16_t perON, uint16_t perOFF);

	LedState getState();

	LedNotifier(GPIO_TypeDef port, uint16_t pin, LedState init = LedState::Off);
	virtual ~LedNotifier();
};

#endif /* INC_LEDNOTIFIER_H_ */
