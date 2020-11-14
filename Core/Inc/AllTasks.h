/*
 * AllTasks.h
 *
 *  Created on: 13.11.2020
 *      Author: Igor
 */

#ifndef INC_ALLTASKS_H_
#define INC_ALLTASKS_H_

#include "main.h"
#include "FreeRTOS.h"
#include "cmsis_os.h"


extern osThreadId BatteryManagerHandle;
extern osThreadId LedUpHandle;


void AllTasks_init();

#endif /* INC_ALLTASKS_H_ */
