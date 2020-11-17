/*
 * BatteryManager.h
 *
 *  Created on: 17.11.2020
 *      Author: Igor
 */

#ifndef INC_BATTERYMANAGER_H_
#define INC_BATTERYMANAGER_H_

#include "main.h"
#include "adc.h"
#include "LipoCell.h"
#include "cmsis_os.h"

#define LIPOCELLS_NUMBER 4				// max number of lipocell objects
#define INDEX_OUT_OF_RANGE_VALUE 0.0f   // number to return in case user want number of cell out of index
#define LIPO_ADC_CHANNEL hadc1

#define CELL1_MAX_VOL  3.7f
#define CELL2_MAX_VOL  7.4f
#define CELL3_MAX_VOL 11.1f
#define CELL4_MAX_VOL 14.8f

#define BATTERY_LOW_VOLTAGE 12.4f
#define BATTERY_DEAD_VOLTAGE 12.0f
#define CELL_LOW_VOLTAGE 3.1f

class BatteryManager {
public:

	void init();
	void process();

	float getBatteryVoltage();
	float getBatteryLevel();
	float getCellVoltage(uint8_t);

	BatteryManager();
	virtual ~BatteryManager();

private:
	void updateMeasurments();
	void checkBatteryLevel();
	void addCells();

	LipoCell* cells[LIPOCELLS_NUMBER];
	uint32_t rawADC[LIPOCELLS_NUMBER]; // IF IT WILL BE IN ONE DMA :/


	enum cell_number{
		cell1,
		cell2,
		cell3,
		cell4
	};

};

#endif /* INC_BATTERYMANAGER_H_ */
