/*
 * HallSensor.h
 *
 *  Created on: 16.11.2020
 *      Author: Igor
 */

#ifndef INC_HALLSENSOR_H_
#define INC_HALLSENSOR_H_


#include "ADC_Tools.h"
#include "Average.h"

#define MAX_HALL_VOLTAGE     5.0f
#define NEUTRAL_HALL_VOLTAGE 2.5f
#define AVERAGE_SIZE_HALL     10


/** Tool that could help in store and conversion of data intended for Hall Sensors.
 * It based on ADC_Tools() class and it help in conversion raw ADC data into current intensity in Amperes
 */
class HallSensor:public ADC_Tools {
public:
	/**
	 * @param sens - float value - sensitive of sensor; value in **[ V/A ]**
	 * @param neutral - float value (optional)- voltage value consider as 0A - normally it's 2.5V, below that
	 * there will be negative ampere values
	 * @param max_vol - float value (optional) - maximum voltage (normally 5.0V)
	 */
	HallSensor(float sens,float neutral = NEUTRAL_HALL_VOLTAGE, float max_vol = MAX_HALL_VOLTAGE);
	HallSensor();

	virtual ~HallSensor();

	/** @param val - uint32_t value - raw value from ADC channel register */
	void update(uint32_t val);


	float getAmpere()const{ return ampere;};
	float getAmpereAvrg();
	float getPercentage();


private:
	float sensivity;
	float ampere;
	float neutral_voltage;
	Average<float, AVERAGE_SIZE_HALL> amp_avrg;

	void convertToAmperes();
	void updateAmperesAvrg();


};

#endif /* INC_HALLSENSOR_H_ */
