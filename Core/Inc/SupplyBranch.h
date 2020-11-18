/*
 * SupplyBranch.h
 *
 *  Created on: 18.11.2020
 *      Author: Igor
 */

#ifndef INC_SUPPLYBRANCH_H_
#define INC_SUPPLYBRANCH_H_

#include "ADC_Tools.h"
#include "Average.h"

class SupplyBranch: public ADC_Tools {
public:

	float getVoltageAvrg();
	float getPercentageAvrg();
	void update(uint32_t raw);
	uint8_t isCloseToZero();

	SupplyBranch(float max, float marg = 0.0f);
	virtual ~SupplyBranch();

private:

	Average<float, 10> avrg;
	float margin;

};

#endif /* INC_SUPPLYBRANCH_H_ */
