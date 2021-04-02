/*
 * ErrorHandler.cpp
 *
 *  Created on: 2 kwi 2021
 *      Author: Igor
 */

#include <ErrorHandler.h>

ErrorHandler::ErrorHandler() {
	errorCounter = 0;

}

ErrorHandler::~ErrorHandler() {
	// TODO Auto-generated destructor stub
}

void ErrorHandler::insert(int line, std::string file, std::string msg) {
	std::string fullMsg = convertToErrorMsg(line, file, msg);



}

std::string ErrorHandler::convertToErrorMsg(int line, std::string file, std::string msg) {
	return file[fileLetters] + std::to_string(line) + msg;
}

void ErrorHandler::addToBuffer(std::string msg){
	buffer[errorCounter] = msg;
	errorCounter++;
}
