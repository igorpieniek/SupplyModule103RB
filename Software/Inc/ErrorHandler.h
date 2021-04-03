/*
 * ErrorHandler.h
 *
 *  Created on: 2 kwi 2021
 *      Author: Igor
 */

#ifndef INC_ERRORHANDLER_H_
#define INC_ERRORHANDLER_H_

#include <string>
#include "CircularBuffer.h"



#define THROW_ERROR()       errorHandler.insert(__LINE__, __FILE__ );
#define THROW_ERROR_M(msg)  errorHandler.insert(__LINE__, __FILE__, msg);

#define ERROR_BUFFER_SIZE 10


class ErrorHandler {
public:
	void insert(int line, std::string file, std::string msg = {} );
	uint8_t isBufferEmpty();
	std::string getLast();
	void clearAll();

	ErrorHandler();
	virtual ~ErrorHandler();

private:
	CircularBuffer<std::string, ERROR_BUFFER_SIZE> buf;

	const uint8_t numberOfFileLetters = 4;
	std::string convertToErrorMsg(int line, std::string file, std::string msg );
	void addToBuffer(std::string msg);
	char getFileExtension(std::string file);
};


extern ErrorHandler errorHandler;
#endif /* INC_ERRORHANDLER_H_ */
