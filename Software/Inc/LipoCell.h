
#include "Average.h"
#include "ADC_Tools.h"
#include "main.h"

#define CELL_MAX_VOLTAGE_DROP 1.2f
#define AVERAGE_SIZE_LIPO      10

/** Class providing tools for lipo cell voltage measurments.
 *
 * It uses Average() class object with fixed number of samples take into calculations (#AVERAGE_SIZE_LIPO) */
class LipoCell:  public ADC_Tools
{

private:
	Average<float, AVERAGE_SIZE_LIPO > avrg;
public:
	/** Define initial parameters, also connected with ADC_Tools(max, min) where min = max - #CELL_MAX_VOLTAGE_DROP
	 * @param max - float value that define maximum voltage
	 */
	LipoCell(float max);

	float getVoltageAvrg();


	float getPercentageAvrg();

	/** @param raw - uint32_t value - raw value from ADC channel register */
	void update(uint32_t raw);

};

