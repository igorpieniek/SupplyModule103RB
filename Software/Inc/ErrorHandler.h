/*
 * ErrorHandler.h
 *
 *  Created on: 2 kwi 2021
 *      Author: Igor
 */

#ifndef INC_ERRORHANDLER_H_
#define INC_ERRORHANDLER_H_

#include <string>



#define THROW_ERROR()       er.insert(__LINE__, __FILE__ );
#define THROW_ERROR_M(msg)  er.insert(__LINE__, __FILE__, msg);

class ErrorHandler {
public:
	void insert(int line, std::string file, std::string msg = {} );
	ErrorHandler();
	virtual ~ErrorHandler();

private:
	std::string buffer[10];
	uint8_t errorCounter;
	const uint8_t fileLetters = 4;
	std::string convertToErrorMsg(int line, std::string file, std::string msg );
	void addToBuffer(std::string msg);

};

#endif /* INC_ERRORHANDLER_H_ */
