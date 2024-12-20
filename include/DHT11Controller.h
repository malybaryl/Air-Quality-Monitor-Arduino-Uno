#ifndef DHT11CONTROLLER_H
#define DHT11CONTROLLER_H

#include <DHT.h>  // Biblioteka obsługująca DHT

#define DHTPIN 9      // Domyślny pin dla DHT11
#define DHTTYPE DHT11 // Typ czujnika

class DHT11Controller {
    DHT dht; // Obiekt DHT (z biblioteki)
    float _temperature;
    float _humidity;
    float _temperatureAverage;
    float _humidityAverage;
    float data[2][25] = {0};
    int dataIndex = 0;
public:
    DHT11Controller();                // Konstruktor domyślny
    DHT11Controller(int DHT11_Pin);   // Konstruktor z wyborem pinu
    float getTemperature();          // Metoda do odczytu temperatury
    float getHumidity();             // Metoda do odczytu wilgotności
    float getTemperatureAverage();          // Metoda do odczytu temperatury
    float getHumidityAverage();             // Metoda do odczytu wilgotności
    void readTemperatureAndHumidity();
    void averageTemperatureAndHumidityHandler();
};

#endif
