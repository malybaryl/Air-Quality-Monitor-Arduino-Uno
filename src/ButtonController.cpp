#include "ButtonController.h"

// Default constructor: uses predefined BUTTON_PIN
ButtonController::ButtonController() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Set pin as input with pull-up resistor
}

// Constructor with a specified pin
ButtonController::ButtonController(int Button_Pin) {
    pinMode(Button_Pin, INPUT_PULLUP);
}

/**
 * Checks if the button was pressed (state changes from HIGH to LOW).
 */
bool ButtonController::buttonPressed() {
    _buttonState = digitalRead(BUTTON_PIN);  // Read current button state
    if (_buttonState == LOW && _lastButtonState == HIGH) {
        delay(50);  // Debouncing
        _lastButtonState = _buttonState;
        return true;
    }
    _lastButtonState = _buttonState;
    return false;
}

/**
 * Changes the display state based on button interaction and the current warning state.
 */
bool ButtonController::changeState(LcdController &lcd, DHT11Controller &dht, PMS5003Controller &pmsSensor, bool warning) {
    if (!warning) {  // Only allow state change if no active warning
        if (_state == 0) {
            lcd.changeLightUp();
            lcd.show_actual_temperature_and_humidity(dht.getTemperature(), dht.getHumidity());
            _state++;
        } else if (_state == 1) {
            lcd.show_actual_pm(pmsSensor.getPM1_0String(), pmsSensor.getPM2_5String(), pmsSensor.getPM10String(), pmsSensor.hasValidData());
            _state++;
        } else if (_state == 2) {
            lcd.show_long_term_temperature_and_humidity(dht.getTemperature(), dht.getHumidity());
            _state++;
        } else if (_state == 3) {
            lcd.show_long_term_pm(pmsSensor.getPM1_0AverageString(), pmsSensor.getPM2_5AverageString(), pmsSensor.getPM10AverageString(), pmsSensor.hasValidData());
            _state++;
        } else {
            lcd.changeLightUp();
            lcd.show_actual_temperature_and_humidity(dht.getTemperature(), dht.getHumidity());
            _state = 0;
        }
    }
    return false;
}
