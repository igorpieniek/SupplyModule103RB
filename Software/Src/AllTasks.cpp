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
#include "TimeTool.h"
#include "FanManager.h"

osThreadId BatteryManagerHandle;
osThreadId LedUpHandle;

void StartBatteryManagerTask(void const * argument);
void StartLedUpTask(void const * argument);

uint32_t receiveADC[2];
float per, volt, perAvrg, voltAvrg ;
uint16_t  currentTime[3]= {0};
uint8_t RXdata;
LedNotifier led(LD2_GPIO_Port, LD2_Pin);
LedNotifier led1(LED1_GPIO_Port, LED1_Pin);
LedNotifier led2(LED2_GPIO_Port, LED2_Pin);



void AllTasks_init(){

	  osThreadDef(BatteryManagerTask, StartBatteryManagerTask, osPriorityNormal, 0, 256);
	  BatteryManagerHandle = osThreadCreate(osThread(BatteryManagerTask), NULL);

	  osThreadDef(LedUpTask, StartLedUpTask, osPriorityNormal, 0, 1024);
	  LedUpHandle = osThreadCreate(osThread(LedUpTask), NULL);


	  HAL_UART_Receive_IT(&huart3, &RXdata, 1);

}


void StartBatteryManagerTask(void const * argument){


	uint8_t blinkFlag=0;
	LipoCell lipo(3.3f);
	HAL_ADC_Start(&hadc1);
	HAL_ADC_Start_DMA(&hadc1, receiveADC, 2);

	for(;;){

		lipo.update(receiveADC[0]);
		per = lipo.getPercentage();
		volt= lipo.getVoltage();
		perAvrg = lipo.getPercentageAvrg();
		voltAvrg= lipo.getVoltageAvrg();

		if(voltAvrg >=2.5f && blinkFlag==0){
			led.blink(500,1000);
			led1.blink(1000,200);
			led2.blink(25);
			blinkFlag = 1;
		}
//		if (voltAvrg< 2.5f){
//			blinkFlag = 0;
//			led.on();
//		}


		osDelay(100);


	}
}

void StartLedUpTask(void const * argument){

	time_tool.init();

	for(;;){


		currentTime[2]= time_tool.getMicros();
		currentTime[0]= time_tool.compareMicros(currentTime[2], currentTime[1]);
		currentTime[1] = currentTime[2];

		led.blink_process();
		led1.blink_process();
		led2.blink_process();
//		osEvent evt = osSignalWait(0x01 | 0x02 | 0x04| 0x08,osWaitForever);
//			if      (evt.value.signals == 0x01){
//				led.on();
//
//			}
//			else if (evt.value.signals == 0x02){
//				led.off();
//
//			}
//			else if (evt.value.signals == 0x04){
//				led.blink_config(100);
//
//			}
//			else if (evt.value.signals== 0x08){
//				led.blink_process();
//
//			}


		osDelay(10);

	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	//static uint16_t per =500;
//	if	   (RXdata == 'n') led.on();
//	else if(RXdata == 'f') led.off();
//	else if(RXdata == 'b') led.blink_config(500,1000);


	HAL_UART_Receive_IT(&huart3, &RXdata, 1);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }


}

