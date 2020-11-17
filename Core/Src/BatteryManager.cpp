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
	return cells[cell4]->getPercentageAvrg(); //TODO: calibrate percents later; wrong in this form
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
	//CHECK MAIN VOLTAGE
	float batt_level = getBatteryVoltage( );
	if (batt_level <= BATTERY_LOW_VOLTAGE){
		//osSignal(BuzzerTask, cell_low_signal); // TODO:add later specyfic taskhandle and signals
		//osSignal(OLEDTask, cell_low_signal);
		return;
	}
	else if (batt_level <= BATTERY_DEAD_VOLTAGE){
		//osSignal(BuzzerTask, cell_low_signal); // TODO:add later specyfic taskhandle and signals
		//osSignal(OLEDTask, cell_low_signal);
		return;
	}
	//CHECK EVERY CELL (if main battery voltage OK)
	for(uint8_t i=0; i <LIPOCELLS_NUMBER; i++){
		if(getCellVoltage(i) <= CELL_LOW_VOLTAGE){
			//osSignal(BuzzerTask, cell_low_signal); // TODO:add later specyfic taskhandle and signals
			//osSignal(OLEDTask, cell_low_signal);
			break;
		}
	}

}

void BatteryManager::addCells(){
	cells[cell1] = new LipoCell(CELL1_MAX_VOL );
	cells[cell2] = new LipoCell(CELL2_MAX_VOL );
	cells[cell3] = new LipoCell(CELL3_MAX_VOL );
	cells[cell4] = new LipoCell(CELL4_MAX_VOL );
}
