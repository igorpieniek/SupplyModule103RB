/*
 * ErrorHandler.cpp
 *
 *  Created on: 2 kwi 2021
 *      Author: Igor
 */

#include <ErrorHandler.h>


ErrorHandler errorHandler;

ErrorHandler::ErrorHandler() {
	errorCounter = 0;
}

ErrorHandler::~ErrorHandler() {
	// TODO Auto-generated destructor stub
}

void ErrorHandler::insert(int line, std::string file, std::string msg) {
	std::string fullMsg = convertToErrorMsg(line, file, msg);
	addToBuffer(fullMsg);
}

std::string ErrorHandler::convertToErrorMsg(int line, std::string file, std::string msg) {
	char fileExt = getFileExtension(file);
	return file.substr(0, fileLetters) +fileExt + std::to_string(line) + msg;
}

char ErrorHandler::getFileExtension(std::string file){
	if(file.find(".c") != std::string::npos) return 'c';
	else 									 return 'h';
}

void ErrorHandler::addToBuffer(std::string msg){
	buffer[errorCounter] = msg;
	incrementBufferIndex();
}

void ErrorHandler::incrementBufferIndex(){
	if (errorCounter < ERROR_BUFFER_SIZE -1){
		errorCounter++;
	}
}

void ErrorHandler::decrementBufferIndex(){
	if(errorCounter > 0){
		errorCounter--;
	}
}

std::string ErrorHandler::getLastError(){
	std::string last = buffer[errorCounter];
	deleteLastError();
	return last;
}



uint8_t ErrorHandler::isBufferEmpty(){
	if(errorCounter == 0) return 1;
	else 				  return 0;
}

void ErrorHandler::deleteLastError(){
	buffer[errorCounter] = "";
	decrementBufferIndex();
}
