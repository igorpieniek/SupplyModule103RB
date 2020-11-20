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
	LedNotifier led(LD2_GPIO_Port, LD2_Pin, &htim4);

	for(;;){
		osEvent evt = osSignalWait(0x01 | 0x02 | 0x04| 0x08,osWaitForever);
			if      (evt.value.signals == 0x01){
				led.on();

			}
			else if (evt.value.signals == 0x02){
				led.off();

			}
			else if (evt.value.signals == 0x04){
				led.blink_config(100);

			}
			else if (evt.value.signals== 0x08){
				led.blink_process();

			}


		osDelay(50);

	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	//static uint16_t per =500;
	if	   (RXdata == 'n') osSignalSet(LedUpHandle, 1 << 0);
	else if(RXdata == 'f') osSignalSet(LedUpHandle, 1 << 1);
	else if(RXdata == 'b') osSignalSet(LedUpHandle, 1 << 2);


	HAL_UART_Receive_IT(&huart3, &RXdata, 1);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }
  if(htim->Instance == TIM4){
	  osSignalSet(LedUpHandle, 0x08);
  }

}

