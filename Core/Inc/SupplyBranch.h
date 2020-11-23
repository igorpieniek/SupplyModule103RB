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
#define AVERAGE_SIZE_SUPPLYBRANCH 		10
#define SUPPLYBRANCH_VOLTAGE_MARGIN 	0.0f
/** Class providing tools for each section voltage measurments
 *
 *  It uses Average() class object with fixed number of samples take into calculations (#AVERAGE_SIZE_SUPPLYBRANCH)
 */
class SupplyBranch: public ADC_Tools {
private:
	Average<float, AVERAGE_SIZE_SUPPLYBRANCH> avrg;
	float margin;

public:

	/** Return voltage [V] moving average of #AVERAGE_SIZE_LIPO last samples.
	 * It overwrite ADC_Tools() abstract method */
	float getVoltageAvrg();

	/** Return percent [%] moving average of #AVERAGE_SIZE_LIPO last samples.
	 * It overwrite ADC_Tools() abstract method  */
	float getPercentageAvrg();

	/** Function called to update the measurments in object.
	 * It provide voltage, percent conversion and adding sample to average object
	 * @param val - uint32_t value - raw value from ADC channel register*/
	void update(uint32_t raw);

	/** Function return **1** when branch voltage is near zero value (in range from 0V to margin defined in  SupplyBranch())*/
	uint8_t isCloseToZero();

	/** Define initial parameters, also connected with ADC_Tools(max)
	 * @param max - float value that define maximum voltage
	 * @param marg - float value (optional) - normally #SUPPLYBRANCH_VOLTAGE_MARGIN - voltage value below which it will be consider as 0V
	 * (po prevent from incorrect result of isCloseToZero() function )*/
	SupplyBranch(float max, float marg = SUPPLYBRANCH_VOLTAGE_MARGIN);
	virtual ~SupplyBranch();


};

#endif /* INC_SUPPLYBRANCH_H_ */
