/*
 * AllTasks.cpp
 *
 *  Created on: 13.11.2020
 *      Author: Igor
 */

#include <AllTasks.h>

osThreadId BatteryManagerHandle;

void StartBatteryManagerTask(void const * argument);

void AllTasks_init(){

	  osThreadDef(BatteryManagerTask, StartBatteryManagerTask, osPriorityNormal, 0, 256);
	  BatteryManagerHandle = osThreadCreate(osThread(BatteryManagerTask), NULL);


}


void StartBatteryManagerTask(void const * argument){

	for(;;){

	}
}
