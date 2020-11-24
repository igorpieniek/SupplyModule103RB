/*
 * InternTemperature.h
 *
 *  Created on: 24.11.2020
 *      Author: Igor
 */

#ifndef INC_INTERNTEMPERATURE_H_
#define INC_INTERNTEMPERATURE_H_
#include "ADC_Tools.h"

#define TEMPERATURE_MAX_VOLTAGE 3.3f  /** [V] MAX voltage level for temperature sensor*/
#define TEMPERATURE_V25			0.76f /** [V] voltage level for 25oC */
#define TEMPETATURE_AVG_SLOPE   0.0025f /** [V/oC] Avg_slope parameter*/

class InternTemperature: public ADC_Tools {
public:
	/** Calculate and return current internal temperature*/
	float getTemperature();

	void update(uint32_t raw);

	InternTemperature();
	virtual ~InternTemperature();



};

#endif /* INC_INTERNTEMPERATURE_H_ */
