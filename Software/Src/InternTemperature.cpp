/*
 * InternTemperature.cpp
 *
 *  Created on: 24.11.2020
 *      Author: Igor
 */

#include <InternTemperature.h>


float InternTemperature::getTemperature(){
	float voltage = getVoltage();
	return convertToTemperature(voltage);
}

void InternTemperature::update(uint32_t raw){
	updateMeasurments(raw);
}

float InternTemperature::convertToTemperature(float volt){
	return ( (TEMPERATURE_V25 - volt) / TEMPETATURE_AVG_SLOPE) + 25.0f; /** datasheet formula*/
}
InternTemperature::InternTemperature():ADC_Tools(TEMPERATURE_MAX_VOLTAGE) {
	// TODO Auto-generated constructor stub

}

InternTemperature::~InternTemperature() {
	// TODO Auto-generated destructor stub
}

