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

	/**Class Init function.
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

	/**Return current voltage of battery */
	float getBatteryVoltage();

	/**Return current state of battery in percentage */
	float getBatteryLevel();

	/**Return specified cell voltage - (reference to the previous cell voltage value)
	 * @param name - cell_number enum - to prevent from incorrect index*/
	float getCellVoltage(cell_name name);


	BatteryManager();
	virtual ~BatteryManager();

private:
	void updateMeasurments(); 	/** Read data using DMA and refresh data stored in every LipoCell object*/
	void checkBatteryLevel(); 	/** Check battery lvl and give info to other tasks - buzzer & oled in case of low level */
	void addCells();			/** add cells and initilize them (to init() ) */

	LipoCell* cells[LIPOCELLS_NUMBER];
	uint32_t rawADC[LIPOCELLS_NUMBER]; // IF IT WILL BE IN ONE DMA :/
};

#endif /* INC_BATTERYMANAGER_H_ */
