#include "ADC_Tools.h"



ADC_Tools::ADC_Tools(float max, uint32_t res ):maxVal(max), bitResolution(res),
					   per(0), value(0){
	maxLevels = 2 << (bitResolution - 1);
}

/*
void ADC_Tools::init(float max, float min, uint32_t res) {
	maxVal = max;
	minVal = min;
	bitResolution = res;
	maxLevels = 2 << (bitResolution - 1);
}
*/

void ADC_Tools::updateMeasurments(uint32_t val){
	value = convertToValue(val);
	per = convertToPercentage(value);

}

float ADC_Tools::convertToValue(uint32_t raw) {
	return ((float)raw * maxVal) / (float)maxLevels;
}

float ADC_Tools::convertToPercentage(float val) {
	return 100.f * ((float)val / maxVal);
}

