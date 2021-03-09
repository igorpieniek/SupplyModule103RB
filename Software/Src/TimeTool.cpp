


#include <TimeTool.h>


TimeTool time_tool;

uint8_t TimeTool::isToolInit(void){
	return microsInitDone;
}
uint16_t TimeTool::getMicros(void){
	return TIMETOOL_TIMER.Instance->CNT;
}
uint16_t TimeTool::compareMicros(uint16_t a, uint16_t b) {
	uint16_t res = 0;
	if (a > b) res = a - b;
	else       res = b - a;
	if (res > uint16Half){
		res = UINT16_MAX- res;
	}
	return res;

}
void TimeTool::init(void) {
	if (!microsInitDone) {
		HAL_TIM_Base_Start(&TIMETOOL_TIMER);
		microsInitDone = 1;
	}
}


TimeTool::TimeTool(): microsInitDone(0) {


}

TimeTool::~TimeTool() {
	// TODO Auto-generated destructor stub
}

