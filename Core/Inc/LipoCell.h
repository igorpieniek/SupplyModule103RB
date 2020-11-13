
#include "Average.h"
#include "ADC_Tools.h"
#include "main.h"

#define MAX_CELL_VOLTAGE 4.5f
#define MIN_CELL_VOLTAGE 0.5f

class LipoCell:  public ADC_Tools
{

private:
	Average<float, 10> avrg;
public:
	LipoCell();
	float getValueAvrg();
	float getPercentageAvrg();

	void update(uint32_t raw);





};

