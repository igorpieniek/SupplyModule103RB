/*
 * EnergyManager.h
 *
 *  Created on: 18.11.2020
 *      Author: Igor
 */

#ifndef INC_ENERGYMANAGER_H_
#define INC_ENERGYMANAGER_H_

#include "main.h"
#include "adc.h"
#include "BatteryManager.h"
#include "HallSensor.h"
#include "SectionSwitch.h"
#include "SupplyBranch.h"
#include "InternTemperature.h"
#include "BatteryManager.h"

#define EM_DMA_ADC_CHANNEL 			 	hadc1 	/**TODO: TARGET HADC2 */
#define EM_DMA_NUMBER_OF_CONVERSION  	10  	/**5 HALL + 4 VOLTAGE MEASURMENTS (+ 1 internal temperature?) */
#define HALL_SENSOR_NUMBER 				5		/** Number of hall senors */
#define SUPPLY_BRANCH_NUMBER 			4		/** Number of section voltage measurements*/
#define SECTION_SWITCH_NUMBER 			5		/** Number of digital switches */

#define HALL_ACS714_50A_SENSIVITY 		0.04f	/** Sensivity of 50A ACS714 hall sensor in [V/A]*/
#define HALL_ACHS7121_SENSIVITY   		0.185f	/** Sensivity of 10A ACHS7121 hall sensor in [V/A]*/

#define BRANCH_5_VOLTAGE 				5.0f	/** Max voltage of 5V branch - TODO: need correction after selection voltage divider */
#define BRANCH_3_VOLTAGE 				3.3f	/** Max voltage of 3.3V branch - TODO: need correction after selection voltage divider */
#define BRANCH_7_VOLTAGE 				7.0f	/** Max voltage of 7V branch - TODO: need correction after selection voltage divider */
#define NEAR_ZERO_VOLTAGE 				0.5f	/** Margin - below this value senction will be consider as turned off  */



//-------------------------------
/** Task class to manage branches energy measurements.
 * * Hall Sensor measurments (HallSensor())
 * * Voltage on each section measurments (SupplyBranch())
 * * Manager of all section switches (SectionSwitch())
 *
 * * Temperature (maybe) - because of sensor available in same ADC
 * */
class EnergyManager {
public:

	struct Section{
		float A;
		float V;
		float P;
	};
private:

	HallSensor hall_sensors[HALL_SENSOR_NUMBER];
	SupplyBranch supply_branches[SUPPLY_BRANCH_NUMBER];
	SectionSwitch section_switches[SECTION_SWITCH_NUMBER];
	InternTemperature temperature;

	uint32_t rawADC[EM_DMA_NUMBER_OF_CONVERSION];
	Section sectionData[HALL_SENSOR_NUMBER]; //motor branach included

	enum DmaIndexes{
		HALL_5_1 	= 0,
		HALL_5_2	= 1,
		HALL_7   	= 2,
		SEC_3    	= 3,
		SEC_5_1  	= 4,
		HALL_3   	= 5,
		SEC_7    	= 6,
		HALL_0   	= 7,
		SEC_5_2 	= 8,
		TEMPERATURE = 9
	};


	void dma_init();
	void hallSensor_init();
	void supplyBranch_init();
	void sectionSwitch_init();

	void update_dma_data();
	void update_section_data();
	void update_switch_data();

	uint8_t checkIfBranchIsRealSwitchON(uint8_t branchnum);
	float powerCalculate(float v, float a);

public:
	/** Enum to define names of cells */
	enum Section_name{
		section_5_1, 	/**< first 5V section - on XL4015 converter */
		section_5_2,	/**< second 5V section - small Pololu converter*/
		section_3,		/**< 3.3V section*/
		section_7,		/**< 7V section - on XL4015*/
		section_motor	/**< Motor section */

	};

	/** Task init function.
	 * * DMA channel init
	 * * Hall sensors init
	 * * Supply Branch init
	 * * Switches init
	 * */
	void init();

	/** Main process of energyManager task
	 * * Update data using DMA (hall sensors and sections voltage data)
	 * * Update section structures (using Section)
	 * * Update switch data - check state according to mechanical slider state
	 * */
	void process();

	/** Turn ON specific section
	 * @warning using section_main() will turn ON all branches - it's not connected with motor and Intel NUC power supply */
	void sectionON(Section_name);

	/** Turn ON specific section
	 * @warning using section_main() will turn OFF all branches - it isn't cut the power supply of motor and Intel NUC */
	void sectionOFF(Section_name);

	/** Return specified Section struct with updated data */
	Section getSectionData(Section_name);

	/** Return current state of specified branch */
	SectionSwitch::Section_state getSectionState(Section_name);

	float getTemperature();


	EnergyManager();
	virtual ~EnergyManager();
};

#endif /* INC_ENERGYMANAGER_H_ */
