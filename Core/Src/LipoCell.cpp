#include "LipoCell.h"



LipoCell::LipoCell():ADC_Tools(MAX_CELL_VOLTAGE){ }

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
