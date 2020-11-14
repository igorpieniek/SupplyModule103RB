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
osThreadId LedUpHandle;

void StartBatteryManagerTask(void const * argument);
void StartLedUpTask(void const * argument);

uint32_t receiveADC[2];
float per, volt, perAvrg, voltAvrg ;


void AllTasks_init(){

	  osThreadDef(BatteryManagerTask, StartBatteryManagerTask, osPriorityNormal, 0, 256);
	  BatteryManagerHandle = osThreadCreate(osThread(BatteryManagerTask), NULL);

	  osThreadDef(LedUpTask, StartLedUpTask, osPriorityBelowNormal, 0, 256);
	  LedUpHandle = osThreadCreate(osThread(LedUpTask), NULL);


}


void StartBatteryManagerTask(void const * argument){


	uint32_t counter = 0;
	LipoCell lipo;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, receiveADC, 2);

	for(;;){

		lipo.update(receiveADC[0]);
		per = lipo.getPercentage();
		volt= lipo.getValue();
		perAvrg = lipo.getPercentageAvrg();
		voltAvrg= lipo.getValueAvrg();

		osDelay(100);


	}
}

void StartLedUpTask(void const * argument){

	for(;;){
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		osDelay(500);
	}
}
