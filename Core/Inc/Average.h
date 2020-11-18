

#ifndef INC_AVERAGE_H_
#define INC_AVERAGE_H_

#include "main.h"

template<typename T , uint8_t s> class Average
{
private:
	T elem[s];
	uint8_t currentIndex; //next array index to be fill with value
	uint8_t numberOfElem; //current number of elements - to protect average during filling array first time
	T avrg;

	void indexIterate(){
		if (numberOfElem != s) numberOfElem++;
		if (currentIndex == (s - 1)) currentIndex = 0;
		else {
			currentIndex++;

		}
	}
	void calculate(){
		T a = 0;
		for (uint8_t i = 0; i < numberOfElem; i++) a += elem[i];
		avrg = a /(T)numberOfElem;
	}

public:
	Average(){
		clear();
	}
	~Average(){

	}

	void insert(T val){
		elem[currentIndex] = val;
		indexIterate();
	}
	void clear(){
		currentIndex = 0;
		numberOfElem = 0;
		for (uint8_t i = 0; i < s; i++) elem[i] = T();
	}
	int size()const { return s; };
	//T& getAvrage()const{ return avrg;};
	T& operator()(){
		this->calculate();
		return this->avrg;
	}


};




//
//template<typename T, uint8_t s>
//Average<T, s>::Average() {
//	clear();
//
//}
//
//
////template<typename T, uint8_t s>
////Average<T, s>::~Average<T, s>() {
////
////
////}
//
//template<typename T, uint8_t s>
//void Average<T, s>::insert(T val) {
//	elem[currentIndex] = val;
//	indexIterate();
//}
//
//template<typename T, uint8_t s>
//void Average<T, s>::clear() {
//	currentIndex = 0;
//	numberOfElem = 0;
//	for (uint8_t i = 0; i < s; i++) elem[i] = T();
//}
//
//template<typename T, uint8_t s>
//void Average<T, s>::indexIterate() {
//	if (numberOfElem != s) numberOfElem++;
//	if (currentIndex == (s - 1)) currentIndex = 0;
//	else {
//		currentIndex++;
//
//	}
//
//}
//
//template<typename T, uint8_t s>
//void Average<T, s>::calculate() {
//	T a = 0;
//	for (uint8_t i = 0; i < numberOfElem; i++) a += elem[i];
//	avrg = a /(T)numberOfElem;
//}
//
//template<typename T, uint8_t s>
//T& Average<T, s>::operator()() {
//	this->calculate();
//	return this->avrg;
//}
#endif /* INC_AVERAGE_H_ */


