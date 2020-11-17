
#include "Average.h"
#include "ADC_Tools.h"
#include "main.h"

#define CELL_MAX_VOLTAGE_DROP 1.2f

class LipoCell:  public ADC_Tools
{

private:
	Average<float, 10> avrg;
public:
	LipoCell(float max);
	float getVoltageAvrg();
	float getPercentageAvrg();

	void update(uint32_t raw);

};

