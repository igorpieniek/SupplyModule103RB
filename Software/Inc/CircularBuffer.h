/*
 * CircularBuffer.h
 *
 *  Created on: 3 kwi 2021
 *      Author: Igor
 */

#ifndef INC_CIRCULARBUFFER_H_
#define INC_CIRCULARBUFFER_H_
#include <cstdint>
#include <utility>

template<typename T, uint8_t MAX_SIZE>
class CircularBuffer{
  public:

    void push(T val);
    void clear();
    void clearLast();
    uint8_t isEmpty();
    uint8_t size()const {return numberOfElem;};
    T pop();
    T& operator[](uint8_t index);

  private:
    T buffer[MAX_SIZE];
    uint8_t currentIndex = 0;
	uint8_t numberOfElem = 0;
    T defaultValue = T{};

    void incrementIndex();
    void decrementIndex();
    void incrementSize();
    void decrementSize();
};

template<typename T, uint8_t MAX_SIZE>
uint8_t CircularBuffer<T, MAX_SIZE>::isEmpty(){
    if(numberOfElem ==0) return 1;
    else                 return 0;
}

template<typename T, uint8_t MAX_SIZE>
void CircularBuffer<T, MAX_SIZE>::push(T val){
  buffer[currentIndex] = val;
  incrementIndex();
  incrementSize();
}

template<typename T, uint8_t MAX_SIZE>
void CircularBuffer<T, MAX_SIZE>::clear(){
    for(uint8_t i=0; i < numberOfElem; i++){
      buffer[i] = T();
    }
    currentIndex = 0;
    numberOfElem = 0;
}

template<typename T, uint8_t MAX_SIZE>
void CircularBuffer<T, MAX_SIZE>::clearLast(){
    decrementIndex();
    buffer[currentIndex] = T();
    decrementSize();
}

template<typename T, uint8_t MAX_SIZE>
T CircularBuffer<T, MAX_SIZE>::pop(){
    decrementIndex();
    T result = buffer[currentIndex];
    buffer[currentIndex] = T();
    decrementSize();
    return result;
}
template<typename T, uint8_t MAX_SIZE>
T& CircularBuffer<T, MAX_SIZE>::operator[](uint8_t index){
    if(index >= 0 && index < numberOfElem){
        return buffer[index];
    }
    else{
        return defaultValue;
    }
}

template<typename T, uint8_t MAX_SIZE>
void CircularBuffer<T, MAX_SIZE>::incrementIndex(){
  if (currentIndex < MAX_SIZE -1){
		currentIndex++;
	}
	else if( currentIndex == MAX_SIZE -1){
		currentIndex = 0;
	}
}

template<typename T, uint8_t MAX_SIZE>
void CircularBuffer<T, MAX_SIZE>::decrementIndex() {
	if (currentIndex > 0){
		currentIndex--;
	}
	else if( currentIndex == 0){
		currentIndex = MAX_SIZE - 1;
	}
}
template<typename T, uint8_t MAX_SIZE>
void CircularBuffer<T, MAX_SIZE>::incrementSize(){
	if (numberOfElem < MAX_SIZE ){
		numberOfElem++;
	}
}
template<typename T, uint8_t MAX_SIZE>
void CircularBuffer<T, MAX_SIZE>::decrementSize(){
	if (numberOfElem > 0){
		numberOfElem--;
	}
}

#endif /* INC_CIRCULARBUFFER_H_ */
