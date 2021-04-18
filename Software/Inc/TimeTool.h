

#ifndef CLASSES_TIMETOOL_H_
#define CLASSES_TIMETOOL_H_

#include "stdint.h"
#include <limits.h>
#include "tim.h"

#define TIMETOOL_TIMER htim4

/** Tool to measure time in miliseconds.
 * It provide function to get current CNT register state and
 * to compare between many measurments - compareMicros().
 * It use timer #TIMETOOL_TIMER
 * @warning #1 Only one global object could be created, but no more!
 * @warning #2 MX_TIMx_Init() have to be called before init() method
 */
extern class TimeTool {

	uint8_t microsInitDone;
	const uint16_t uint16Half= UINT16_MAX / 2;
public:
	/**Init function - it does't use MX_TIMx_Init() function - it have to be called before
	 */
	void init(void);

	uint8_t isToolInit(void);
	uint16_t getMicros(void);

	/** To compare two timer states and return the difference.
	 * @return value in range <0, #UINT16_MAX/2 >
	 */
	uint16_t compareMicros(uint16_t a, uint16_t b);

	TimeTool();
	virtual ~TimeTool();
}time_tool;


#endif /* CLASSES_TIMETOOL_H_ */
