/*
 * SectionSwitch.h
 *
 *  Created on: 18.11.2020
 *      Author: Igor
 */

#ifndef INC_SECTIONSWITCH_H_
#define INC_SECTIONSWITCH_H_

#include "main.h"
#include "gpio.h"

/** Tools for switching ON / OFF specific supply branch.
 * It help in easy way to set branch in right state. It solve the
 * problem of branch state - when pin is set to OFF but branch is still ON because
 * of mechanical slider switch -updateRealStateON()
 */
class SectionSwitch {
public:

	/** To specify current state of supply branch*/
	enum Section_state{
		OFF,
		ON,
		ON_BY_SLIDER /** state when section pin is set to OFF but mechanical switch was turned ON */
	};

	Section_state getState()const {return realState;};

	void on();
	void off();

	/**Change internal state to real one.
	 *  It update info about supply branch, but without changing pin state to ON
	 *  @warning It must be called when current state is OFF, but branch voltage is higher than 0V !
	 *  */
	void updateRealStateON();

	/** @param st - GPIO_PinState (optional) - initial state of supply branch - normally ON */
	SectionSwitch(GPIO_TypeDef* port , uint16_t pin, GPIO_PinState st = GPIO_PIN_SET );
	SectionSwitch();
	virtual ~SectionSwitch();


private:
	GPIO_TypeDef * port;
	uint16_t pin;
	Section_state realState;
};

#endif /* INC_SECTIONSWITCH_H_ */
