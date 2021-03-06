/*
 * HallSensor.cpp
 *
 *  Created on: 16.11.2020
 *      Author: Igor
 */

#include <HallSensor.h>

HallSensor::HallSensor(float sens,float neutral, float max_vol):
				ADC_Tools(max_vol), sensivity(sens), neutral_voltage(neutral) { }

HallSensor::~HallSensor() {
	// TODO Auto-generated destructor stub
}


void HallSensor::update(uint32_t val ){
	ADC_Tools::updateMeasurments(val);
	convertToAmperes();
	updateAmperesAvrg();
}

float HallSensor::getAmpereAvrg(){
	return amp_avrg();
}

float HallSensor::getPercentage(){
	return (2* ADC_Tools::getPercentage()) -100; // <-100; 100> conversion
}

void HallSensor::convertToAmperes(){
	ampere = (ADC_Tools::getVoltage() - neutral_voltage) / sensivity;
}

void HallSensor::updateAmperesAvrg(){
	amp_avrg.insert(ampere);
}
