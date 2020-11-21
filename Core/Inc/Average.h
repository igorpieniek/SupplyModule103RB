
#include "main.h"

/// **Moving average**\n
/// Class for objects which gather specified data and calculate moving average.
/// During first fill of object, average will be calculate in range <0, n>,
/// where **n** is a number of elements inserted to this moment -
/// even if **n < s** (where **s** is a fixed  maximal number of data)

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

	///  Method to add value that will be take into consideration during average calculation
	///  @param val  value that will be added to average
	void insert(T val){
		elem[currentIndex] = val;
		indexIterate();
	}

	/// Clear average buffer
	void clear(){
		currentIndex = 0;
		numberOfElem = 0;
		for (uint8_t i = 0; i < s; i++) elem[i] = T();
	}

	/// Function to return maximal number of elements in average
	/// @return uint8_t size - maximal number of elements in average
	uint8_t size()const { return s; };
	//T& getAvrage()const{ return avrg;};


	/// Overload of () operator
	/// @return average of all data collected in object
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



