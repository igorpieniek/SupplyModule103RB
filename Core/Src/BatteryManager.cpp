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
	return cells[cell4]->getVoltageAvrg();
}

float BatteryManager::getBatteryLevel(){
	return cells[cell4]->getPercentageAvrg();
}

float BatteryManager::getCellVoltage(uint8_t index){
	if( index <0 || index > LIPOCELLS_NUMBER ) return INDEX_OUT_OF_RANGE_VALUE; // out of index
	if (index == cell1) return cells[cell1]->getVoltageAvrg();					// first cell
	return cells[index]->getVoltageAvrg() - cells[index -1]->getVoltageAvrg();  // every next cell
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
		cells[i]->update(rawADC[i]);
	}
}

void BatteryManager::checkBatteryLevel(){

}

void BatteryManager::addCells(){
	cells[cell1] = new LipoCell(CELL1_MAX_VOL );
	cells[cell2] = new LipoCell(CELL2_MAX_VOL );
	cells[cell3] = new LipoCell(CELL3_MAX_VOL );
	cells[cell4] = new LipoCell(CELL4_MAX_VOL );
}
