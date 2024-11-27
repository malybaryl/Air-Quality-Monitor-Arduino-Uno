#include "DHT11Controller.h"

// Konstruktor domyślny
DHT11Controller::DHT11Controller() : dht(DHTPIN, DHTTYPE) {
    dht.begin();
}

// Konstruktor z parametrem pinu
DHT11Controller::DHT11Controller(int DHT11_Pin) : dht(DHT11_Pin, DHTTYPE) {
    dht.begin();
}

float DHT11Controller::getTemperature(){
    return _temperature;
}

float DHT11Controller::getHumidity(){
    return _humidity;
}

float DHT11Controller::getTemperatureAverage(){
    return _temperatureAverage;
}

float DHT11Controller::getHumidityAverage(){
    return _humidityAverage;
}

void DHT11Controller::readTemperatureAndHumidity(){
    _temperature = dht.readTemperature();
    _humidity = dht.readHumidity();
    this->averageTemperatureAndHumidityHandler();
}

void DHT11Controller::averageTemperatureAndHumidityHandler(){
    data[0][dataIndex] = _temperature;
    data[1][dataIndex] = _humidity;
    dataIndex = (dataIndex + 1) % 25;
    float temperature_sum = 0;
    float humidity_sum = 0;
    for (int i = 0; i < 25; i++){
        if (data[0][i] < 0.1 && data[1][i] <= 0.1){
            _temperatureAverage = temperature_sum / (i + 1);
            _humidityAverage = humidity_sum / (i + 1);
            break;
        }
        temperature_sum += data[0][i];
        humidity_sum += data[1][i];
        if (i == 24){
            _temperatureAverage = temperature_sum / 25;
            _humidityAverage = humidity_sum / 25;
        }
    }
}