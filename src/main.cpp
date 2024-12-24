#include <Arduino.h>
#include "LcdController.h"
#include "DHT11Controller.h"
#include "ButtonController.h"
#include "PMS5003Controller.h"
#include "BuzzerController.h"
#include "Delay.h"

// Global objects for hardware controllers
LcdController lcdScreen;             // Manages LCD display
DHT11Controller dhtSensor;           // Handles DHT11 temperature and humidity sensor
ButtonController button;             // Handles button input and its states
PMS5003Controller pmsSensor;         // Handles PMS5003 air quality sensor
BuzzerController buzzer;             // Controls buzzer for alerts

// Timing and state management
unsigned long lastUpdate = 0;        // Tracks the last time sensors were updated
unsigned long lastAlert = 0;         // Tracks the last alert timestamp
const unsigned long updateInterval = 1000;           // 1-second update interval for sensors
const unsigned long alertCooldownInterval = 60000;   // 1-minute cooldown for alerts
bool warning = false;                // Indicates if a warning is active
bool alertCooldown = false;          // Tracks if the system is in cooldown mode

void setup() {
    lcdScreen.print("Initializing...", true);
    Delay::delay_ms(3000);

    // Initial readings from sensors
    dhtSensor.readTemperatureAndHumidity();
    pmsSensor.readPM();
    button.setState(1);  // Default button state
}

void loop() {
    // Handle button presses
    if (button.buttonPressed()) {
        Delay::delay_ms(200);  // Debouncing delay
        if (warning) {
            // Disable alarm if active and start cooldown
            warning = false;
            alertCooldown = true;
            lastAlert = millis();
            buzzer.turnOff();
        } else {
            // Change state if no active warning
            button.changeState(lcdScreen, dhtSensor, pmsSensor, warning);
            
        }
    }

    // Manage alert cooldown
    if (alertCooldown && millis() - lastAlert > alertCooldownInterval) {
        alertCooldown = false;  // End cooldown
    }

    // Periodic sensor updates
    if (millis() - lastUpdate > updateInterval) {
        lastUpdate = millis();

        // Read sensor data
        dhtSensor.readTemperatureAndHumidity();
        
        pmsSensor.readPM();
        bool pmsDataRead = pmsSensor.hasValidData();
        

        // Trigger warning if thresholds exceeded and no cooldown
        if (!alertCooldown) {
            warning = pmsSensor.warning();
            if (warning) {
                buzzer.turnOn();
               
            }
        }

        if (!warning){
        // Update LCD display based on the current state
            switch (button.getState()) {
                case 0:
                case 1:
                    lcdScreen.show_actual_temperature_and_humidity(
                        dhtSensor.getTemperature(),
                        dhtSensor.getHumidity()
                    );
                    break;
                case 2:
                    lcdScreen.show_actual_pm(
                        pmsSensor.getPM1_0String(),
                        pmsSensor.getPM2_5String(),
                        pmsSensor.getPM10String(),
                        pmsDataRead
                    );
                    break;
                case 3:
                    lcdScreen.show_long_term_temperature_and_humidity(
                        dhtSensor.getTemperatureAverage(),
                        dhtSensor.getHumidityAverage()
                    );
                    break;
                case 4:
                    lcdScreen.show_long_term_pm(
                        pmsSensor.getPM1_0AverageString(),
                        pmsSensor.getPM2_5AverageString(),
                        pmsSensor.getPM10AverageString(),
                        pmsDataRead
                    );
                    break;
                default:
                    lcdScreen.print("Invalid State!", true);
                    break;
            }
        }
        else 
        {
            lcdScreen.show_warning();
        }
        
    }
}
