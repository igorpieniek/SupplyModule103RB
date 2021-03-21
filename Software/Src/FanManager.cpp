/*
 * FanManager.cpp
 *
 *  Created on: 20 mar 2021
 *      Author: Igor
 */

#include <FanManager.h>

FanManager fans;

FanManager::FanManager(void){};


void FanManager::init() {
	fans[0].init(&FAN1_TIMER, FAN1_TIMER_CHANNEL);
	fans[1].init(&FAN2_TIMER, FAN2_TIMER_CHANNEL);
	fans[2].init(&FAN3_TIMER, FAN3_TIMER_CHANNEL);
	fans[3].init(&FAN4_TIMER, FAN4_TIMER_CHANNEL);

	//if dynamic allocation problem will be solved:
//	fans[0] = new Fan(&FAN1_TIMER, FAN1_TIMER_CHANNEL);
//	fans[1] = new Fan(&FAN2_TIMER, FAN2_TIMER_CHANNEL);
//	fans[2] = new Fan(&FAN3_TIMER, FAN3_TIMER_CHANNEL);
//	fans[3] = new Fan(&FAN4_TIMER, FAN4_TIMER_CHANNEL);
}

void FanManager::process() {
	osEvent evt = osSignalWait(	(uint8_t)TemperatureSignals::COOLDOWN |
								(uint8_t)TemperatureSignals::HIGH_TEMPERATURE |
								(uint8_t)TemperatureSignals::OVERHEATED
							   , osWaitForever);
	switch(evt.value.signals){
		case (uint8_t)TemperatureSignals::COOLDOWN:
			startCooldownProcedure();
			break;
		case (uint8_t)TemperatureSignals::HIGH_TEMPERATURE:
			startHighTemperatureProcedure();
			break;
		case (uint8_t)TemperatureSignals::OVERHEATED:
			startOverheatedProcedure();
			break;
	}

}


void FanManager::off(FanName name) {
	fans[ (uint8_t) name ].off();
}

void FanManager::onLowSpeed(FanName name) {
	fans[ (uint8_t) name ].on(Fan::LOW);
}

void FanManager::onNormalSpeed(FanName name) {
	fans[ (uint8_t) name ].on(Fan::NORMAL);
}

void FanManager::onHighSpeed(FanName name) {
	fans[ (uint8_t) name ].on(Fan::HIGH);
}

FanManager::~FanManager() {

}

void FanManager::startCooldownProcedure() {
	fans[(uint8_t) FanName::Fan1].on(Fan::LOW);
	fans[(uint8_t) FanName::Fan2].on(Fan::LOW);
}

void FanManager::startHighTemperatureProcedure() {
	fans[(uint8_t) FanName::Fan1].on(Fan::NORMAL);
	fans[(uint8_t) FanName::Fan2].on(Fan::NORMAL);
}

void FanManager::startOverheatedProcedure() {
	fans[(uint8_t) FanName::Fan1].on(Fan::HIGH);
	fans[(uint8_t) FanName::Fan2].on(Fan::HIGH);
}
