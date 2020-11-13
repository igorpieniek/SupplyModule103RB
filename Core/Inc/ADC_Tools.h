
#include "main.h"

#define STANDARD_RESOLUTION 12

class ADC_Tools
{
public:
	float getValue()const				   { return value; };
	virtual float getValueAvrg()      { return value; };
	float getPercentage()const			   { return per; };
	virtual float getPercentageAvrg() { return per; };

	//virtual ~ADC_Tools();

private:
	uint16_t bitResolution;
	float maxVal;
	float minVal;
	uint32_t maxLevels;


	float value;
	float per;


protected:
	ADC_Tools(float max, float min, uint32_t res = STANDARD_RESOLUTION);
	//void init(float max, float min, uint32_t res = STANDARD_RESOLUTION);
	void updateMeasurments(uint32_t val);
	float convertToValue(uint32_t);
	float convertToPercentage(float);

};

