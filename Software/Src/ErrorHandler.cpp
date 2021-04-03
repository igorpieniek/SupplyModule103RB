/*
 * ErrorHandler.cpp
 *
 *  Created on: 2 kwi 2021
 *      Author: Igor
 */

#include "ErrorHandler.h"



ErrorHandler errorHandler;

ErrorHandler::ErrorHandler() {}

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
	buf.push(msg);
}

uint8_t ErrorHandler::isBufferEmpty(){
	return buf.isEmpty();
}


std::string ErrorHandler::getLast(){
  return buf.pop();
}

void ErrorHandler::clearAll(){
	buf.clear();
}

ErrorHandler::~ErrorHandler() {
	// TODO Auto-generated destructor stub
}
