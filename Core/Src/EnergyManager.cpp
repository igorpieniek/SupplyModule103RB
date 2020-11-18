/*
 * EnergyManager.cpp
 *
 *  Created on: 18.11.2020
 *      Author: Igor
 */

#include <EnergyManager.h>

EnergyManager::EnergyManager() {
	// TODO Auto-generated constructor stub

}

EnergyManager::~EnergyManager() {
	// TODO Auto-generated destructor stub
}

void EnergyManager::init(){
	hallSensor_init();
	supplyBranch_init();
	sectionSwitch_init();
}

void EnergyManager::hallSensor_init(){
	hall_sensors[motor] = 	 new HallSensor(HALL_ACS714_50A_SENSIVITY);
	hall_sensors[hall_5_1] = new HallSensor(HALL_ACHS7121_SENSIVITY );
	hall_sensors[hall_5_2] = new HallSensor(HALL_ACHS7121_SENSIVITY );
	hall_sensors[hall_3] =   new HallSensor(HALL_ACHS7121_SENSIVITY );
	hall_sensors[hall_7] =   new HallSensor(HALL_ACHS7121_SENSIVITY );

}

void EnergyManager::supplyBranch_init(){

}

void EnergyManager::sectionSwitch_init(){

}
