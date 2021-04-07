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
#include "Oled/SSD1306.h"
#include "Interface/Interface_manager.h"
#include "i2c.h"

osThreadId BatteryManagerHandle;
osThreadId LedUpHandle;
osThreadId OledTaskHandle;
osThreadId InterfaceTaskHandle;

void StartBatteryManagerTask(void const * argument);
void StartLedUpTask(void const * argument);
void StartOledTask(void const *argument);
void StartInterfaceTask(void const *argument);

SSD1306* oled2;

void AllTasks_init(){

	  osThreadDef(BatteryManagerTask, StartBatteryManagerTask, osPriorityNormal, 0, 256);
	  BatteryManagerHandle = osThreadCreate(osThread(BatteryManagerTask), NULL);

	  osThreadDef(LedUpTask, StartLedUpTask, osPriorityNormal, 0, 1024);
	  LedUpHandle = osThreadCreate(osThread(LedUpTask), NULL);

	  osThreadDef(OledTask, StartOledTask, osPriorityBelowNormal, 0, 128);
	  OledTaskHandle = osThreadCreate(osThread(OledTask), NULL);

	  osThreadDef(InterfaceTask, StartInterfaceTask, osPriorityNormal, 0, 1024);
	  InterfaceTaskHandle = osThreadCreate(osThread(InterfaceTask), NULL);


	  HAL_UART_Receive_IT(&huart3, &RXdata, 1);

}

void StartOledTask(void const *argument){
	for(;;){
		oled2->oledInterrupt();
		osDelay(50);
	}
}
void StartInterfaceTask(void const *argument){
	Interface_manager* Interface2;
	SSD1306::OledSettingsI2C i2c_settings;
	i2c_settings.address = 0x3C<<1;
	i2c_settings.hi2c = &hi2c1;
	oled2 = new SSD1306(i2c_settings);
	oled2->changeDMA(SSD1306::SET_ON);
	oled2->init();
	HAL_Delay(5);
	Interface2=new Interface_manager(&huart3, oled2);
  for(;;)
  {
	Interface2->interrupt();
    osDelay(100);
  }
}

void StartBatteryManagerTask(void const * argument){

	for(;;){

		osDelay(100);


	}
}

void StartLedUpTask(void const * argument){


	for(;;){

		osDelay(10);
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

