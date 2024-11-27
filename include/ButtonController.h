#ifndef BUTTONCONTROLLER_H
#define BUTTONCONTROLLER_H

#include <Arduino.h>
#include "LcdController.h"
#include "DHT11Controller.h"
#include "PMS5003Controller.h"

#define BUTTON_PIN 7  // Pin connected to the button

/**
 * Manages button state and input for interaction with the system.
 */
class ButtonController {
    int _state = 0;                    // Current button state
    bool _lastButtonState = HIGH;      // Previous button state (for edge detection)
    bool _buttonState = HIGH;          // Current button state

public:
    ButtonController();               // Default constructor
    ButtonController(int Button_Pin); // Constructor with pin assignment

    void setState(int state) { _state = state; };  // Sets the button state
    int getState() { return _state; };            // Retrieves the current state
    bool buttonPressed();                         // Checks if button was pressed
    bool changeState(LcdController &lcd, DHT11Controller &dht, PMS5003Controller &pmsSensor, bool warning);
};

#endif
