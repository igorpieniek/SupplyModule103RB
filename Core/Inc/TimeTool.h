

#ifndef CLASSES_TIMETOOL_H_
#define CLASSES_TIMETOOL_H_

#include "stdint.h"
#include <limits.h>
#include "tim.h"

#define TIMETOOL_TIMER htim4

extern class TimeTool {

	uint8_t microsInitDone;
	const uint16_t uint16Half= UINT16_MAX / 2;
public:

	void init(void);
	uint8_t isToolInit(void);
	uint16_t getMicros(void);
	uint16_t compareMicros(uint16_t a, uint16_t b);

	TimeTool();
	virtual ~TimeTool();
}time_tool;


#endif /* CLASSES_TIMETOOL_H_ */
