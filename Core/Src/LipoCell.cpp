#include "LipoCell.h"



LipoCell::LipoCell(float max ):ADC_Tools(max,max-CELL_MAX_VOLTAGE_DROP){ }

void LipoCell::update(uint32_t val) {
	updateMeasurments(val);
	avrg.insert(getVoltage());
}


float LipoCell::getVoltageAvrg() {
	return avrg();
}

float LipoCell::getPercentageAvrg() {
	float valAvrg = getVoltageAvrg();
	return convertToPercentage(valAvrg);
}
