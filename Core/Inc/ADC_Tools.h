
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
	/** Return value in Volts
	 * @return float value - [V]
	 */
	float getVoltage()const				{ return value; };

	/** Abstract method to return voltage value average.
	 * Need to be defined in derived class - in case it won't be defined it return getVoltage() result
	 * @return float voltageAverage or float voltage
	 */
	virtual float getVoltageAvrg()      { return value; };

	/** Abstract method to return percent value in reference to maximum and minimum voltage value.
	 * Could be defined in derived class - normally it returned percent value in voltage range <max, min>
	 * (defined in Constructor ADC_Tools())
	 * @return float voltageAverage or voltage
	 */
	virtual float getPercentage()const	{ return per; };

	/** Abstract method to return voltage value average.
	 * Need to be defined in derived class - in case it won't be defined it return getVoltage() result
	 * @return float voltageAverage or float voltage
	 */
	virtual float getPercentageAvrg()   { return per; };

	//virtual ~ADC_Tools();

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

	/** Function called to update the measurments in object.
	 * It provide voltage and percent conversion
	 * @param val - uint32_t value - raw value from ADC channel register
	 */
	void updateMeasurments(uint32_t val);

	/** Function that convert raw ADC channel register value into voltage using inital configuration
	 * @param raw - uint32_t value - raw value from ADC channel register
	 * @return float value of voltage in [V]
	 */
	float convertToVoltage(uint32_t raw);

	/**Function that convert stored in object voltage value into percents in referance to
	 * range <min_voltage, max_voltage> (initial configuration)
	 * @param val - float value - voltage value in [V]
	 * @return float value in percents [%]
	 */
	float convertToPercentage(float val);

};
#endif /* INC_ADC_TOOLS_H_ */
