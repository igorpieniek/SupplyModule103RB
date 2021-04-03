/*
 * ErrorHandler.cpp
 *
 *  Created on: 2 kwi 2021
 *      Author: Igor
 */

#include "ErrorHandler.h"


ErrorHandler errorHandler;

ErrorHandler::ErrorHandler() {
	currentIndex = 0;
	currentSize = 0;
}

void ErrorHandler::insert(int line, std::string file, std::string msg) {
	std::string fullMsg = convertToErrorMsg(line, file, msg);
	addToBuffer(fullMsg);
}

std::string ErrorHandler::convertToErrorMsg(int line, std::string file, std::string msg) {
	char fileExt = getFileExtension(file);
	return file.substr(0, numberOfFileLetters)
		   + fileExt
		   + std::to_string(line)
	       + msg;
}


char ErrorHandler::getFileExtension(std::string file){
	if(file.find(".c") != std::string::npos) return 'c';
	else 									 return 'h';
}

void ErrorHandler::addToBuffer(std::string msg){
	buffer[currentIndex] = msg;
	incrementIndex();
	incrementBufferSize();
}


void ErrorHandler::incrementIndex(){
	if (currentIndex < ERROR_BUFFER_SIZE -1){
		currentIndex++;
	}
	else if( currentIndex == ERROR_BUFFER_SIZE -1){
		currentIndex = 0;
	}
}

void ErrorHandler::decrementIndex() {
	if (currentIndex > 0){
		currentIndex--;
	}
	else if( currentIndex == 0){
		currentIndex = ERROR_BUFFER_SIZE - 1;
	}
}

uint8_t ErrorHandler::isBufferEmpty(){
	if(currentSize == 0) return 1;
	else 				 return 0;
}

void ErrorHandler::incrementBufferSize(){
	if (currentSize < ERROR_BUFFER_SIZE ){
		currentSize++;
	}
}

void ErrorHandler::decrementBufferSize(){
	if (currentSize > 0){
		currentSize--;
	}
}

std::string ErrorHandler::getLast(){
	decrementIndex();
	std::string last = buffer[currentIndex];
	deleteLastError();
	decrementBufferSize();
	return last;
}

void ErrorHandler::deleteLastError(){
	buffer[currentIndex] = "";
}

void ErrorHandler::clearAll(){
	for(uint8_t i=0; i < ERROR_BUFFER_SIZE; i++){
		buffer[i] = "";
	}
	currentIndex = 0;
	currentSize = 0;
}

ErrorHandler::~ErrorHandler() {
	// TODO Auto-generated destructor stub
}









