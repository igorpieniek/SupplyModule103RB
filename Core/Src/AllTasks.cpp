/*
 * AllTasks.cpp
 *
 *  Created on: 13.11.2020
 *      Author: Igor
 */

#include <AllTasks.h>
#include <stdio.h>
#include "LipoCell.h"
#include "usart.h"
#include "adc.h"

osThreadId BatteryManagerHandle;

void StartBatteryManagerTask(void const * argument);

void AllTasks_init(){

	  osThreadDef(BatteryManagerTask, StartBatteryManagerTask, osPriorityNormal, 0, 256);
	  BatteryManagerHandle = osThreadCreate(osThread(BatteryManagerTask), NULL);


}


void StartBatteryManagerTask(void const * argument){

	uint32_t receiveADC[2];
	uint32_t counter = 0;
	LipoCell lipo;



	for(;;){

		lipo.update(receiveADC[0]);
		float res = lipo.getPercentage();
		char buf[15];
		uint16_t size = sprintf( buf, "Percent: %.2f\n", (float)res);
		HAL_UART_Transmit(&huart3, (uint8_t*)buf,size, 10);
		osDelay(100);


	}
}
