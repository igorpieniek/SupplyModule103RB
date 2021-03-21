/*
 * FanManager.h
 *
 *  Created on: 20 mar 2021
 *      Author: Igor
 */

/*
 * FanManager.h
 *
 *  Created on: 24.11.2020
 *      Author: Igor
 */

#ifndef INC_FANMANAGER_H_
#define INC_FANMANAGER_H_

#include "main.h"
#include "tim.h"
#include "Fan.h"

#define FAN1_TIMER			htim3			//htim12
#define FAN1_TIMER_CHANNEL	TIM_CHANNEL_1

#define FAN2_TIMER			htim3				//htim12
#define FAN2_TIMER_CHANNEL	TIM_CHANNEL_2

#define FAN3_TIMER			htim3
#define FAN3_TIMER_CHANNEL	TIM_CHANNEL_3

#define FAN4_TIMER			htim3
#define FAN4_TIMER_CHANNEL	TIM_CHANNEL_4


#define NUMBER_OF_FANS		4

enum class FanName: uint8_t{
	Fan1 = 0,
	Fan2,
	Fan3,
	Fan4
};

/**Task class to manage all fans
 *
 */
class FanManager {
private:
	Fan fans[NUMBER_OF_FANS];

public:

	void init();

	/**All fans process
	 * * Check internal temperature
	 * * Processing all signals (send by communication module, energy manager, battery manager)
	 */
	void process();


	void onLowSpeed(FanName name);
	void onNormalSpeed(FanName name);
	void onHighSpeed(FanName name);

	void off(FanName name);

	FanManager();
	virtual ~FanManager();

};

extern FanManager fans;
#endif /* INC_FANMANAGER_H_ */
