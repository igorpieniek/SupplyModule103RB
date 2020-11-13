/*
 * Average.cpp
 *
 *  Created on: 13.11.2020
 *      Author: Igor
 */

#include "Average.h"


template<typename T, uint8_t s>
Average<T, s>::Average() {
	clear();

}


//template<typename T, uint8_t s>
//Average<T, s>::~Average<T, s>() {
//
//
//}

template<typename T, uint8_t s>
void Average<T, s>::insert(T val) {
	elem[currentIndex] = val;
	indexIterate();
}

template<typename T, uint8_t s>
void Average<T, s>::clear() {
	currentIndex = 0;
	numberOfElem = 0;
	for (uint8_t i = 0; i < s; i++) elem[i] = T();
}

template<typename T, uint8_t s>
void Average<T, s>::indexIterate() {
	if (numberOfElem != s) numberOfElem++;
	if (currentIndex == (s - 1)) currentIndex = 0;
	else {
		currentIndex++;

	}

}

template<typename T, uint8_t s>
void Average<T, s>::calculate() {
	T a = 0;
	for (uint8_t i = 0; i < numberOfElem; i++) a += elem[i];
	avrg = a /(T)numberOfElem;
}

template<typename T, uint8_t s>
T& Average<T, s>::operator()() {
	this->calculate();
	return this->avrg;
}

