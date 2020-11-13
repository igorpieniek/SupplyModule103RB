#include "LipoCell.h"



LipoCell::LipoCell():ADC_Tools(MAX_CELL_VOLTAGE, MIN_CELL_VOLTAGE){
	//ADC_Tools::init(MAX_CELL_VOLTAGE, MIN_CELL_VOLTAGE);

}

void LipoCell::update(uint32_t val) {
	updateMeasurments(val);
	avrg.insert(getValue());
}


float LipoCell::getValueAvrg() {
	return avrg();
}

float LipoCell::getPercentageAvrg() {
	float valAvrg = getValueAvrg();
	return convertToPercentage(valAvrg);
}
