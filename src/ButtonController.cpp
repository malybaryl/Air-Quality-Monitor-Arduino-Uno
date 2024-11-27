#include "ButtonController.h"

ButtonController::ButtonController() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);  
}

// Konstruktor z parametrem pinu
ButtonController::ButtonController(int Button_Pin) {
    pinMode(Button_Pin, INPUT_PULLUP);  
}

bool ButtonController::buttonPressed() {
    _buttonState = digitalRead(BUTTON_PIN);  // Odczyt stanu przycisku
    // Sprawdzenie, czy stan zmienił się z HIGH na LOW (naciśnięcie)
    if (_buttonState == LOW && _lastButtonState == HIGH) {
        delay(50);  // Krótkie opóźnienie dla eliminacji drgań
        _lastButtonState = _buttonState;
        return true;  // Przyciski naciśnięty
    }
    _lastButtonState = _buttonState;  // Zaktualizuj stan przycisku
    return false;  // Jeśli przycisk nie jest naciśnięty, zwróć false
}

void ButtonController::changeState(LcdController &lcd, DHT11Controller &dht, PMS5003Controller &pmsSensor) {
    if (_state == 0) {
        lcd.changeLightUp();
        lcd.show_actual_temperature_and_humidity(dht.getTemperature(), dht.getHumidity());
        _state++;
    } else if (_state == 1) {
        lcd.show_actual_pm(pmsSensor.getPM1_0String(), pmsSensor.getPM2_5String(), pmsSensor.getPM10String(), false);
        _state++;
    } else if (_state == 2) {
        lcd.show_long_term_temperature_and_humidity(dht.getTemperature(), dht.getHumidity());
        _state++;
    } else if (_state == 3) {
        lcd.show_long_term_pm();
        _state++;
    } else {
        lcd.changeLightUp();
        lcd.show_actual_temperature_and_humidity(dht.getTemperature(), dht.getHumidity());
        _state = 0;
    } 
}
