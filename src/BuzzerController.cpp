#include "BuzzerController.h"



/**
 * Default constructor: uses predefined buzzer pin (8).
 * Initializes the pin as output and sets it to LOW state.
 */
BuzzerController::BuzzerController() : buzzerPin(8) 
{ 
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW); 
}

/**
 * Constructor with pin assignment.
 * Initializes the specified pin as output and sets it to LOW state.
 * @param pin Pin number connected to the buzzer.
 */
BuzzerController::BuzzerController(int pin) : buzzerPin(pin) 
{
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW);
}

/**
 * Turns the buzzer on (HIGH state).
 */
void BuzzerController::turnOn()
{
    digitalWrite(buzzerPin, HIGH);
}


/**
 * Turns the buzzer off (LOW state).
 */
void BuzzerController::turnOff() 
{
    digitalWrite(buzzerPin, LOW);
}
