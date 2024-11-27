#ifndef BUZZERCONTROLLER_H
#define BUZZERCONTROLLER_H

#include <Arduino.h>

class BuzzerController {
private:
    int buzzerPin;

public:
    // Konstruktor bezargumentowy
    BuzzerController();

    // Konstruktor argumentowy
    BuzzerController(int pin);

    // Metoda włączająca buzzer
    void turnOn();

    // Metoda wyłączająca buzzer
    void turnOff();
};

#endif // BUZZERCONTROLLER_H
