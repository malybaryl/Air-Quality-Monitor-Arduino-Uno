#include <Arduino.h>
#include "LcdController.h"  // Ścieżka do pliku nagłówkowego LedController
#include "DHT11Controller.h" // Ścieżka do pliku nagłówkowego DHT11Controller
#include "ButtonController.h"
#include "PMS5003Controller.h"

// Globalne zmienne
LcdController lcdScreen;
DHT11Controller dhtSensor;
ButtonController button;
PMS5003Controller pmsSensor;
unsigned long lastUpdate = 0;      
const unsigned long updateInterval = 1000; 

void setup() {
    lcdScreen.print("Initializing...", true);
    delay(4000);
    dhtSensor.readTemperatureAndHumidity();
    pmsSensor.readPM();
    button.setState(1);
}

void loop() {
    if (button.buttonPressed()) {
        delay(200);
        button.changeState(lcdScreen, dhtSensor, pmsSensor);
    }

    if (millis() - lastUpdate > updateInterval) {
      lastUpdate = millis();
      int actualState = button.getState();
      // Odczyt danych z czujników
      dhtSensor.readTemperatureAndHumidity();
      pmsSensor.readPM();
      bool pmsDataRead = pmsSensor.checkData();

      // odświeżenie ekranu
      
      if (actualState == 0 || actualState == 1) {
        lcdScreen.show_actual_temperature_and_humidity(dhtSensor.getTemperature(), dhtSensor.getHumidity());
      } else if (actualState == 2) {
        lcdScreen.show_actual_pm(pmsSensor.getPM1_0String(), pmsSensor.getPM2_5String(), pmsSensor.getPM10String(), pmsDataRead);
      }
      
    }
    
}
