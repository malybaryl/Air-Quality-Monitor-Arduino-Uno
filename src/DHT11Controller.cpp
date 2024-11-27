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

void DHT11Controller::readTemperatureAndHumidity(){
    _temperature = dht.readTemperature();
    _humidity = dht.readHumidity();
}