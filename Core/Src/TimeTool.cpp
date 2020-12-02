


#include <TimeTool.h>


TimeTool time_tool;

uint8_t TimeTool::isToolInit(void){
	return microsInitDone;
}
uint32_t TimeTool::getMicros(void){
	return TIMETOOL_TIMER.Instance->CNT;
}
int32_t TimeTool::compareMicros(uint32_t a, uint32_t b) {
	return (int32_t)(a - b);
}
void TimeTool::init(void) {
	if (!microsInitDone) {
		HAL_TIM_Base_Start(&TIMETOOL_TIMER);
		microsInitDone = 1;
	}
}


TimeTool::TimeTool(): microsInitDone(0) {
	// TODO Auto-generated constructor stub

}

TimeTool::~TimeTool() {
	// TODO Auto-generated destructor stub
}

