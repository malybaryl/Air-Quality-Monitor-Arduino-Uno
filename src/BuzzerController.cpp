#include "BuzzerController.h"

// Konstruktor bezargumentowy
BuzzerController::BuzzerController() : buzzerPin(8) { // Domyślny pin 8
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW); // Ustaw buzzer jako wyłączony
}

// Konstruktor argumentowy
BuzzerController::BuzzerController(int pin) : buzzerPin(pin) {
    pinMode(buzzerPin, OUTPUT);
    digitalWrite(buzzerPin, LOW); // Ustaw buzzer jako wyłączony
}

// Metoda włączająca buzzer
void BuzzerController::turnOn() {
    digitalWrite(buzzerPin, HIGH);
}

// Metoda wyłączająca buzzer
void BuzzerController::turnOff() {
    digitalWrite(buzzerPin, LOW);
}
