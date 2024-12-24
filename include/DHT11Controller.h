#ifndef DHT11CONTROLLER_H
#define DHT11CONTROLLER_H

#include <DHT.h> 

#define DHTPIN 9      
#define DHTTYPE DHT11 

class DHT11Controller {
    DHT dht; 
    float _temperature;
    float _humidity;
    float _temperatureAverage;
    float _humidityAverage;
    float data[2][25] = {0};
    int dataIndex = 0;
public:
    DHT11Controller();              
    DHT11Controller(int DHT11_Pin);
    float getTemperature();         
    float getHumidity();           
    float getTemperatureAverage();          
    float getHumidityAverage();            
    void readTemperatureAndHumidity();
    void averageTemperatureAndHumidityHandler();
};

#endif
