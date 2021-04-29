#include "Interface_manager.h"
#include "usart.h"
#include "string"
#define BUTTON_1 'a' // left
#define BUTTON_2 'd' // right
#define BUTTON_3 's'// down
#define SPECIAL_BUTTON 224
#define INTERVAL 0.1

Interface_manager::Interface_manager(UART_HandleTypeDef* huart, SSD1306* oled){
    Ssd_1306 = new Interface ;
    uart_interface=huart;
    this->oled=oled;
    errors = new ErrorsOLED();
}

ErrorsOLED* Interface_manager::getErrorObject(){
	return this->errors;
}

void Interface_manager::init(){
    HAL_UART_Receive_IT(uart_interface, &button, 1);
}

void Interface_manager::interrupt(){
	if(button!=0)
		Ssd_1306->sendAction( readKey() ) ;
	Ssd_1306->refresh() ;
	display() ;
	button=0;
    HAL_UART_Receive_IT(uart_interface, (uint8_t*)&button, 1);
}

Interface_Element::Button Interface_manager::readKey(){
	switch(this->button){
		case BUTTON_1:
			return Interface_Element::LEFT_BUTTON;
        case BUTTON_2:
            return Interface_Element::RIGHT_BUTTON;
        case BUTTON_3:
        	return Interface_Element::ENTER ;
        break;
    }
}
void Interface_manager::display(){
	oled->fillBuffer(BufferSSD1306::Black);

    if( Ssd_1306->isNoChangeableErrorCounting() ){
        oled->writeString("No change", 6, 11, BufferSSD1306::White, 2, 2);
        oled->writeString("possible", 7, 10, BufferSSD1306::White, 2, 17);
    }
    else{
    	oled->writeString( (char*)Ssd_1306->getParameterHeadline().c_str(), 7, 10, BufferSSD1306::White, 2, 2);
        if( !(Ssd_1306->isBackFromSubListParameter()) && !(Ssd_1306->hasSubList()) ){
            if( Ssd_1306->isVisibleValue() ){
//            	char value;
//            	value = Ssd_1306->getParameterValue();
//            	string unit =  Ssd_1306->getParameterUnit();
//            	char* text = new char(sizeof(value) + unit.length());
//            	memcpy(text, &value, sizeof(value));
//            	memcpy(&text[sizeof(value)], unit.c_str(), unit.length());
//        		oled->writeString( text, 7, 10, BufferSSD1306::White, 2, 17);
            	uint16_t value = Ssd_1306->getParameterValue();
            	string unit = Ssd_1306->getParameterUnit();
            	string text = to_string(value) + unit;
            	oled->writeString((char*)text.c_str(), 7, 10, BufferSSD1306::White, 2,17);
            }
            else{
                for( uint16_t i = (Ssd_1306->getParameterValue() )*10 ; i > 0 ; i /= 10)
                    oled->writeString(" ", 7, 10, BufferSSD1306::White, 2, 2);
                oled->writeString((char*)Ssd_1306->getParameterUnit().c_str(), 7, 10, BufferSSD1306::White, 2, 17);
            }
        }
    }
    //oled->writeString("ABCDGHIJKLMVWXYZ", "font11x18", BufferSSD1306::Black, 5, 36);
    oled->writeDefaultString("ABCD", BufferSSD1306::Black, 5, 36);
}
