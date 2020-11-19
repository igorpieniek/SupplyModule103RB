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
#include "LedNotifier.h"

osThreadId BatteryManagerHandle;
osThreadId LedUpHandle;

void StartBatteryManagerTask(void const * argument);
void StartLedUpTask(void const * argument);

uint32_t receiveADC[2];
float per, volt, perAvrg, voltAvrg ;
uint8_t RXdata;



void AllTasks_init(){

	  osThreadDef(BatteryManagerTask, StartBatteryManagerTask, osPriorityNormal, 0, 256);
	  BatteryManagerHandle = osThreadCreate(osThread(BatteryManagerTask), NULL);

	  osThreadDef(LedUpTask, StartLedUpTask, osPriorityBelowNormal, 0, 256);
	  LedUpHandle = osThreadCreate(osThread(LedUpTask), NULL);


	  HAL_UART_Receive_IT(&huart3, &RXdata, 1);

}


void StartBatteryManagerTask(void const * argument){


	uint32_t counter = 0;
//	LipoCell lipo;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, receiveADC, 2);

	for(;;){

//		lipo.update(receiveADC[0]);
//		per = lipo.getPercentage();
//		volt= lipo.getVoltage();
//		perAvrg = lipo.getPercentageAvrg();
//		voltAvrg= lipo.getVoltageAvrg();


		osDelay(100);


	}
}

void StartLedUpTask(void const * argument){
	for(;;){

	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	static uint16_t per =500;
	if		(RXdata == 'n') led.on();
	else if (RXdata == 'f') led.off();
	else if (RXdata == 'b'){
		led.blink(per);
		per +=500;
	}
	else if (RXdata == 'c'){
		if(per >500) per -=500;
		led.blink(per);
	}
	HAL_UART_Receive_IT(&huart3, &RXdata, 1);
}


