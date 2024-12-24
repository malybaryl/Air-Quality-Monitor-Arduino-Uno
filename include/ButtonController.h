#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include <Arduino.h>
#include "LcdController.h"
#include "DHT11Controller.h"
#include "PMS5003Controller.h"

#define BUTTON_PIN 7  

class ButtonController {
    int _state = 0;                   
    bool _lastButtonState = HIGH;     
    bool _buttonState = HIGH;         

public:
    ButtonController();               
    ButtonController(int Button_Pin); 

    void setState(int state) { _state = state; };  
    int getState() { return _state; };            
    bool buttonPressed();                         
    bool changeState(LcdController &lcd, DHT11Controller &dht, PMS5003Controller &pmsSensor, bool warning);
};

#endif
