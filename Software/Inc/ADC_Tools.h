
#include "main.h"



#ifndef INC_ADC_TOOLS_H_
#define INC_ADC_TOOLS_H_





#define STANDARD_RESOLUTION    12
#define STANDARD_MINIMUM_VOLT 0.0f


/** Abstract class to help in ADC data conversion.
 *
 */
class ADC_Tools
{
public:

	float getVoltage()const				{ return value; };

	virtual float getVoltageAvrg()      { return value; };

	virtual float getPercentage()const	{ return per; };

	virtual float getPercentageAvrg()   { return per; };


private:
	uint16_t bitResolution;
	float maxVal;
	float minVal;
	uint32_t maxLevels;


	float value;
	float per;


protected:

	/**
	 * @param max - float value - maximum voltage
	 * @param min - float value (optional) - voltage consider as minimum in percentage calculation (normally 0.0V)
	 * @param res - uint32_t value (optional) - resolution; number of bits (normally it's 12)
	 */
	ADC_Tools(float max, float min = STANDARD_MINIMUM_VOLT, uint32_t res = STANDARD_RESOLUTION);
	//void init(float max, float min, uint32_t res = STANDARD_RESOLUTION);

	/** @param val - uint32_t value - raw value from ADC channel register */
	void updateMeasurments(uint32_t val);

	/** Function that convert raw ADC channel register value into voltage using initial configuration
	 * @param raw - uint32_t value - raw value from ADC channel register */
	float convertToVoltage(uint32_t raw);

	/**@param val - float value - voltage value in [V]*/
	float convertToPercentage(float val);

};
#endif /* INC_ADC_TOOLS_H_ */
