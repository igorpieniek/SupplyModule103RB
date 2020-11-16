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

#define MAX_HALL_VOLTAGE 5.0f
#define NEUTRAL_HALL_VOLTAGE 2.5f



class HallSensor:public ADC_Tools {
public:
	HallSensor(float sens);
	virtual ~HallSensor();

	void update(uint32_t);

	float getAmpere()const{ return ampere;};
	float getAmpereAvrg();
	float getVoltage();
	float getPercentage();


private:
	float sensivity;
	float ampere;
	Average<float, 10> Amp_avrg;

	void convertToAmperes();


};

#endif /* INC_HALLSENSOR_H_ */
