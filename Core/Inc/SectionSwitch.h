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

class SectionSwitch {
public:

	enum Section_state{
		OFF,
		ON,
		ON_BY_SLIDER // SECTION PIN IS OFF BUT SLIDER SWITCH TURN ON SUPPLYBRANCH
	};
	Section_state getState()const {return realState;};
	void on();
	void off();
	void updateRealStateON(); //to solve problem of current istate when pin state = OFF, but switch is ON


	SectionSwitch(GPIO_TypeDef *, uint16_t pin, GPIO_PinState st = GPIO_PIN_SET );
	virtual ~SectionSwitch();


private:
	GPIO_TypeDef * port;
	uint16_t pin;
	Section_state realState;
};

#endif /* INC_SECTIONSWITCH_H_ */
