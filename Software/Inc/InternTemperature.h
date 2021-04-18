/*
 * InternTemperature.h
 *
 *  Created on: 24.11.2020
 *      Author: Igor
 */

#ifndef INC_INTERNTEMPERATURE_H_
#define INC_INTERNTEMPERATURE_H_

#include "ADC_Tools.h"

#define TEMPERATURE_MAX_VOLTAGE 3.3f 	/** [V] MAX voltage level for temperature sensor*/
#define TEMPERATURE_V25			0.76f 	/** [V] voltage level for 25oC */
#define TEMPETATURE_AVG_SLOPE   0.0025f /** [V/oC] Avg_slope parameter*/

/**Tool to help with temperature sensor calculations.
 * Use datasheet formula : \n
 *     **T = ( [Vsense - V25] / Avg_slope] + 25** \n
 * where: \n
 * Vsense = current sensor voltage \n
 * V25 = #TEMPERATURE_V25	\n
 * Avg_slope = #TEMPETATURE_AVG_SLOPE
 */
class InternTemperature: public ADC_Tools {
public:
	float getTemperature();

	/** @param raw - uint32_t raw ADC channel register data*/
	void update(uint32_t raw);

	InternTemperature();
	virtual ~InternTemperature();
private:
	float convertToTemperature(float volt);
};

#endif /* INC_INTERNTEMPERATURE_H_ */
