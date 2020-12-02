

#ifndef CLASSES_TIMETOOL_H_
#define CLASSES_TIMETOOL_H_

#include "stdint.h"
#include "tim.h"

#define TIMETOOL_TIMER htim4

extern class TimeTool {

	uint8_t microsInitDone;
public:

	void init(void);
	uint8_t isToolInit(void);
	uint32_t getMicros(void);
	int32_t compareMicros(uint32_t a, uint32_t b);

	TimeTool();
	virtual ~TimeTool();
}time_tool;


#endif /* CLASSES_TIMETOOL_H_ */
