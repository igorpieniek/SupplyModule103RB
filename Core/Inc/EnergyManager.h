/*
 * EnergyManager.h
 *
 *  Created on: 18.11.2020
 *      Author: Igor
 */

#ifndef INC_ENERGYMANAGER_H_
#define INC_ENERGYMANAGER_H_

#include "main.h"
#include "HallSensor.h"
#include "SectionSwitch.h"
#include "SupplyBranch.h"


#define EM_DMA_NUMBER_OF_CONVERSION  9 //5 HALL + 4 VOLTAGE MEASURMENTS (+ 1 internal temperature?)
#define HALL_SENSOR_NUMBER 5
#define SUPPLY_BRANCH_NUMBER 4
#define SECTION_SWITCH_NUMBER 4

#define HALL_ACS714_50A_SENSIVITY 0.04f
#define HALL_ACHS7121_SENSIVITY   0.185f


class EnergyManager {
private:

	HallSensor* hall_sensors[HALL_SENSOR_NUMBER];
	SupplyBranch* supply_branches[SUPPLY_BRANCH_NUMBER];
	SectionSwitch* section_switches[SECTION_SWITCH_NUMBER];
	enum hall_index{
		motor,
		hall_5_1,
		hall_5_2,
		hall_3,
		hall_7
	};
	enum supplybranch_index{
		supply_5_1,
		supply_5_2,
		supply_3,
		supply_7
	};
	enum switch_index{
		switch_5_1,
		switch_5_2,
		switch_3,
		switch_7
	};

	void hallSensor_init();
	void supplyBranch_init();
	void sectionSwitch_init();
public:
	struct Section{
		float A; //Ampere
		float V; //Voltage
		float P; //Power
	};
	void init();

	EnergyManager();
	virtual ~EnergyManager();
};

#endif /* INC_ENERGYMANAGER_H_ */
