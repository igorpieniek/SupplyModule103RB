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
	dma_init();
	hallSensor_init();
	supplyBranch_init();
	sectionSwitch_init();
}


void EnergyManager::process(){
	//update all data
}



void EnergyManager::dma_init(){
	HAL_ADC_Start(&EM_DMA_ADC_CHANNEL);
	HAL_ADC_Start_DMA(&EM_DMA_ADC_CHANNEL, rawADC, EM_DMA_NUMBER_OF_CONVERSION);
}
void EnergyManager::hallSensor_init(){
	hall_sensors[section_5_1] = new HallSensor(HALL_ACHS7121_SENSIVITY );
	hall_sensors[section_5_2] = new HallSensor(HALL_ACHS7121_SENSIVITY );
	hall_sensors[section_3] =   new HallSensor(HALL_ACHS7121_SENSIVITY );
	hall_sensors[section_7] =   new HallSensor(HALL_ACHS7121_SENSIVITY );
	hall_sensors[MOTOR_SW_INDEX] = 	   new HallSensor(HALL_ACS714_50A_SENSIVITY);

}

void EnergyManager::supplyBranch_init(){
	supply_branches[section_5_1] = new SupplyBranch(BRANCH_5_VOLTAGE,NEAR_ZERO_VOLTAGE );
	supply_branches[section_5_2] = new SupplyBranch(BRANCH_5_VOLTAGE,NEAR_ZERO_VOLTAGE );
	supply_branches[section_3] =   new SupplyBranch(BRANCH_3_VOLTAGE,NEAR_ZERO_VOLTAGE );
	supply_branches[section_7] =   new SupplyBranch(BRANCH_7_VOLTAGE,NEAR_ZERO_VOLTAGE );
}

void EnergyManager::sectionSwitch_init(){
//	section_switches[section_5_1] =      new SectionSwitch(SW_5_1_GPIO_Port,  SW_5_1_Pin);
//	section_switches[section_5_2] =      new SectionSwitch(SW_5_2_GPIO_Port,  SW_5_2_Pin);
//	section_switches[section_3] =        new SectionSwitch(SW_3_GPIO_Port,    SW_3_Pin);
//	section_switches[section_7] =        new SectionSwitch(SW_7_GPIO_Port,    SW_7_Pin);
//	section_switches[section_main] =   new SectionSwitch(SW_MAIN_GPIO_Port, SW_MAIN_Pin);

}

void EnergyManager::update_all(){
	/*rawADC is a table to be written by DMA. It store data in specific order:
	 * 0. Hall_5_1
	 * 1. Hall_5_2
	 * 2. Hall_7
	 * 3. Section_3
	 * 4. Section_5_1
	 * 5. Hall_3
	 * 6. Section_7
	 * 7. Hall_0 (MOTOR)
	 * 8. Section_5_2
	 */
}


