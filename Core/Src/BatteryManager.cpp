/*
 * BatteryManager.cpp
 *
 *  Created on: 17.11.2020
 *      Author: Igor
 */

#include <BatteryManager.h>

void BatteryManager::init(){
	HAL_ADC_Start(&LIPO_ADC_CHANNEL);
	HAL_ADC_Start_DMA(&LIPO_ADC_CHANNEL, rawADC, LIPOCELLS_NUMBER);

	addCells();
}

void BatteryManager::process(){
	updateMeasurments();
	checkBatteryLevel();
}

float BatteryManager::getBatteryVoltage(){

}

float BatteryManager::getBatteryLevel(){

}

float BatteryManager::getCellVoltage(uint8_t){

}

BatteryManager::BatteryManager() {
	// TODO Auto-generated constructor stub

}

BatteryManager::~BatteryManager() {
	// TODO Auto-generated destructor stub
	delete [] cells;
}


void BatteryManager::updateMeasurments(){
	for(uint8_t i =0; i < LIPOCELLS_NUMBER; i++){
		cells[i]->updateMeasurments(rawADC[i]);
	}
}

void BatteryManager::checkBatteryLevel(){

}

void BatteryManager::addCells(){
	for(uint8_t i =0; i < LIPOCELLS_NUMBER; i++){
		cells[i]= new LipoCell();
	}
}
