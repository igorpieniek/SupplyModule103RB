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

#include "RtosTool.h"
#include "RtosMessages.h"

osThreadId BatteryManagerHandle;
osThreadId LedUpHandle;

void StartBatteryManagerTask(void const * argument);
void StartLedUpTask(void const * argument);

RtosTool tool;
Data1 data;
Data1 data2;

void AllTasks_init(){

	  tool.registerQueue<Data1>(3);

	  osThreadDef(BatteryManagerTask, StartBatteryManagerTask, osPriorityNormal, 0, 1024);
	  BatteryManagerHandle = osThreadCreate(osThread(BatteryManagerTask), NULL);

	  osThreadDef(LedUpTask, StartLedUpTask, osPriorityNormal, 0, 1024);
	  LedUpHandle = osThreadCreate(osThread(LedUpTask), NULL);

}


void StartBatteryManagerTask(void const * argument){
	data.x = 9;
	data.y = 8;
	data.z = 7;
	for(;;){
		tool.insert<Data1>(data);
		 data.x++;
		 data.y++;
		 data.z++;

		osDelay(500);


	}
}

void StartLedUpTask(void const * argument){
	for(;;){
		while(tool.pop<Data1>(&data2)){
			HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		}
		osDelay(200);
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	//static uint16_t per =500;
//	if	   (RXdata == 'n') led.on();
//	else if(RXdata == 'f') led.off();
//	else if(RXdata == 'b') led.blink_config(500,1000);


//	HAL_UART_Receive_IT(&huart3, &RXdata, 1);
}


void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

  if (htim->Instance == TIM1) {
    HAL_IncTick();
  }


}

