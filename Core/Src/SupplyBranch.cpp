/*
 * SupplyBranch.cpp
 *
 *  Created on: 18.11.2020
 *      Author: Igor
 */

#include <SupplyBranch.h>

SupplyBranch::SupplyBranch(float max, float marg):ADC_Tools(max), margin(marg)  {
	// TODO Auto-generated constructor stub

}

SupplyBranch::~SupplyBranch() {
	// TODO Auto-generated destructor stub
}

void SupplyBranch::update(uint32_t raw){
	updateMeasurments(raw);
	avrg.insert(getVoltage());
}

float SupplyBranch::getVoltageAvrg(){
	return avrg();
}

float SupplyBranch::getPercentageAvrg(){
	float valAvrg = getVoltageAvrg();
	return convertToPercentage(valAvrg);
}


uint8_t SupplyBranch::isCloseToZero(){
	if( getVoltageAvrg() <= margin) return 1;
	else return 0;
}
