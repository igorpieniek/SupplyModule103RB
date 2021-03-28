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
	update_dma_data();
	update_section_data();
	update_switch_data();
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
	hall_sensors[section_motor] = 	   new HallSensor(HALL_ACS714_50A_SENSIVITY);

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



void EnergyManager::update_dma_data(){
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
	 * 9. Intern Temperature
	 */
	hall_sensors[section_5_1]->update(rawADC[ HALL_5_1 ]);
	hall_sensors[section_5_2]->update(rawADC[ HALL_5_2 ]);
	hall_sensors[section_3]->update(rawADC[ HALL_3 ]);
	hall_sensors[section_7]->update(rawADC[ HALL_7 ]);
	hall_sensors[section_motor]->update(rawADC[ HALL_0 ]);

	supply_branches[section_5_1]->update(rawADC[ SEC_5_1 ]);
	supply_branches[section_5_2]->update(rawADC[ SEC_5_2 ]);
	supply_branches[section_3]->update(rawADC[ SEC_3 ]);
	supply_branches[section_7]->update(rawADC[ SEC_7 ]);

	temperature.update(rawADC[ TEMPERATURE ]);
}

void EnergyManager::update_section_data(){
	// gather all data in Section struct
	for(uint8_t i =0; i < 4; i++){ //TODO: do smth with this "number"
		sectionData[i].A = hall_sensors[i]->getAmpereAvrg();
		sectionData[i].V = supply_branches[i]->getVoltageAvrg();
		sectionData[i].P =  powerCalculate(sectionData[i].V, sectionData[i].A);
	}
	sectionData[section_motor].A = hall_sensors[section_motor]->getAmpereAvrg();
	//TODO: add after define batterymanager and adding to target project
	//sectionData[section_motor].V = battery_manager.getBatteryVoltage();
	sectionData[section_motor].P = powerCalculate(sectionData[section_motor].A, sectionData[section_motor].V);
}

float EnergyManager::powerCalculate(float v, float a) {
	return v * a;
}

void EnergyManager::update_switch_data(){
	//check the "false/ positive" problem - when pin is off but all branch is still turn on
	for(uint8_t i=0; i <SECTION_SWITCH_NUMBER -1; i++){ // -1 because main switch can't do anything when branch was turn on by slider
		if(checkIfBranchIsRealSwitchON( i ) ){
			section_switches[i]->updateRealStateON();
		}
	}
}

uint8_t EnergyManager::checkIfBranchIsRealSwitchON(uint8_t branchnum){
	return (!( supply_branches[branchnum]->isCloseToZero() ) && ( section_switches[branchnum]->getState() == SectionSwitch::OFF));

}

void EnergyManager::sectionON(Section_name sec){
	section_switches[sec]->on();
}
void EnergyManager::sectionOFF(Section_name sec){
	section_switches[sec]->off();
}

EnergyManager::Section EnergyManager::getSectionData(Section_name sec){
	return sectionData[sec];
}

float EnergyManager::getTemperature() {
	return temperature.getTemperature();

}
