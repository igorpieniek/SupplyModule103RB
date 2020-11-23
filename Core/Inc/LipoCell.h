
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

	/** Return voltage [V] moving average of #AVERAGE_SIZE_LIPO last samples.
	 * It overwrite ADC_Tools() abstract method */
	float getVoltageAvrg();

	/** Return percent [%] moving average of #AVERAGE_SIZE_LIPO last samples.
	 * It overwrite ADC_Tools() abstract method  */
	float getPercentageAvrg();

	/** Function called to update the measurments in object.
	 * It provide voltage, percent conversion and adding sample to average object
	 * @param val - uint32_t value - raw value from ADC channel register
	 */
	void update(uint32_t raw);

};

