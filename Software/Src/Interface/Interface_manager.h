#include "Interface.h"
#include "main.h"

#ifndef INTERFACEMANAGER_H_
#define INTERFACEMANAGER_H_
#ifdef __cplusplus

class Interface_manager{
public:
	Interface_manager(UART_HandleTypeDef* huart) ;
	void interrupt();
	void init();
private:
	Interface *Ssd_1306 ;
	Interface_Element::Button readKey() ;
	void display() ;
	uint8_t button;
	UART_HandleTypeDef* uart_interface;
};
#endif
#endif /* INTERFACEMANAGER_H_ */
