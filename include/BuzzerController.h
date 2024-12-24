#ifndef BUZZERCONTROLLER_H
#define BUZZERCONTROLLER_H

#include <Arduino.h>

class BuzzerController {
private:
    int buzzerPin;

public:

    BuzzerController();

    BuzzerController(int pin);


    void turnOn();


    void turnOff();
};

#endif 
