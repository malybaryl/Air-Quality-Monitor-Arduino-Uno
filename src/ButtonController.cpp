#include "ButtonController.h"


/**
 * Default constructor for ButtonController.
 * Initializes the button pin as an input with an internal pull-up resistor.
 */

ButtonController::ButtonController() {
    pinMode(BUTTON_PIN, INPUT_PULLUP);  // Set pin as input with pull-up resistor
}


/**
 * Constructor for ButtonController with pin assignment.
 * Sets up the specified button pin as an input with an internal pull-up resistor.
 * 
 * @param Button_Pin The pin number connected to the button.
 */

ButtonController::ButtonController(int Button_Pin) {
    pinMode(Button_Pin, INPUT_PULLUP);
}


/**
 * Detects if the button has been pressed by checking for a transition
 * from a high to low state, indicating a button press event.
 * Implements debouncing to prevent false triggers.
 * 
 * @return true if the button has been pressed, false otherwise.
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
 * Changes the display state based on the button press and the warning state.
 * 
 * @param lcd Reference to the LcdController object
 * @param dht Reference to the DHT11Controller object
 * @param pmsSensor Reference to the PMS5003Controller object
 * @param warning Whether there is an active warning
 * 
 * @return false (not currently used)
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
