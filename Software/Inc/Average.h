

#ifndef INC_AVERAGE_H_
#define INC_AVERAGE_H_

#include "main.h"

/** Moving average.
 * Class for objects which gather specified data and calculate moving average.
 * Class use templates and it need to be declared with:
 * \n **typename T** - type of data to be calculted
 * \n **uint8_t s** -  fixed  maximal number of samples take into average
 *
 * During first fill of object, average will be calculate in range <0, n>,
 * where **n** is a number of elements inserted to this moment -
 * even if **n < s**
 *
 * ### Example
 * ~~~~~~~~~~~~~~~~~~~~~~~~.cpp
 *  Average<float, 15> avrg;
 *  avrg.insert(5.42);
 *  avrg.insert(1.23);
 *  float result = avrg();
 *  ~~~~~~~~~~~~~~~~~~~~~~~~
 */

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

	uint8_t size()const { return s; };

	T& operator()(){
		this->calculate();
		return this->avrg;
	}


};

#endif /* INC_AVERAGE_H_ */


