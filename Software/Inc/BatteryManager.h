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

#define LIPOCELLS_NUMBER 4				/** max number of lipocell objects */
#define INDEX_OUT_OF_RANGE_VALUE 0.0f   /** number to return in case user want number of cell out of index */
#define LIPO_ADC_CHANNEL hadc1

#define CELL1_MAX_VOL  4.2f
#define CELL2_MAX_VOL  8.4f
#define CELL3_MAX_VOL 12.6f
#define CELL4_MAX_VOL 16.8f

#define BATTERY_LOW_VOLTAGE 12.4f //TODO: change
#define BATTERY_DEAD_VOLTAGE 12.0f
#define CELL_LOW_VOLTAGE 3.1f

/** Task class to manage all battery operations
 *
 */
class BatteryManager {
public:

	/**Task Init function.
	 * Init of DMA ADC channels and LipoCell() objects */
	void init();

	/**Main Process of task
	 * * measurements update
	 * * check battery level and sending signals in case of battery low level
	 */
	void process();

	/** Enum to define names of cells */
	enum cell_name{
		cell1,
		cell2,
		cell3,
		cell4
	};

	float getBatteryVoltage();
	float getBatteryLevel();
	float getCellVoltage(cell_name name);

	BatteryManager();
	virtual ~BatteryManager();

private:
	void updateMeasurments();
	void checkBatteryLevel();
	void addCells();

	LipoCell* cells[LIPOCELLS_NUMBER];
	uint32_t rawADC[LIPOCELLS_NUMBER];
};

#endif /* INC_BATTERYMANAGER_H_ */
