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

uint32_t receiveADC[2];


void AllTasks_init(){

	  osThreadDef(BatteryManagerTask, StartBatteryManagerTask, osPriorityNormal, 0, 256);
	  BatteryManagerHandle = osThreadCreate(osThread(BatteryManagerTask), NULL);


}


void StartBatteryManagerTask(void const * argument){


	uint32_t counter = 0;
	LipoCell lipo;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, receiveADC, 2);

	for(;;){

		lipo.update(receiveADC[0]);
		float res = lipo.getPercentage();
		char buf[15];
		uint16_t size = sprintf( &buf[0], "Percent: %.2f\n", res);
		HAL_UART_Transmit(&huart3, (uint8_t*)buf,size, 10);
		osDelay(100);


	}
}
