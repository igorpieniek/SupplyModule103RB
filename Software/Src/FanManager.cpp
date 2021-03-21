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
//	fans[0] = new Fan(&FAN1_TIMER, FAN1_TIMER_CHANNEL);
//	fans[1] = new Fan(&FAN2_TIMER, FAN2_TIMER_CHANNEL);
//	fans[2] = new Fan(&FAN3_TIMER, FAN3_TIMER_CHANNEL);
//	fans[3] = new Fan(&FAN4_TIMER, FAN4_TIMER_CHANNEL);
}

void FanManager::process() {
	for(uint8_t i=0; i < NUMBER_OF_FANS; i++){
		if(!fans[i].isOn()){
			fans[i].on(Fan::NORMAL);
		}
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

