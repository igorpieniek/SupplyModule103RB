/*
 * HallSensor.h
 *
 *  Created on: 16.11.2020
 *      Author: Igor
 */

#ifndef INC_HALLSENSOR_H_
#define INC_HALLSENSOR_H_


#include "ADC_Tools.h"

#define MAX_VOLTAGE 3.5f
#define MIN_VOLTAGE 0.0f



class HallSensor:public ADC_Tools {
public:
	HallSensor();
	virtual ~HallSensor();

private:

};

#endif /* INC_HALLSENSOR_H_ */
