#include "DHT11Controller.h"

/**
 * Default constructor for DHT11Controller.
 * This constructor does not take any arguments and defaults to using pin 9 for the DHT11 sensor.
 * It also begins the DHT11 sensor.
 */
DHT11Controller::DHT11Controller() : dht(DHTPIN, DHTTYPE) 
{
    dht.begin();
}

/**
 * Constructor for DHT11Controller with pin selection.
 * Initializes the DHT11 sensor on the specified pin and begins communication.
 * 
 * @param DHT11_Pin The pin number to which the DHT11 sensor is connected.
 */

DHT11Controller::DHT11Controller(int DHT11_Pin) : dht(DHT11_Pin, DHTTYPE) 
{
    dht.begin();
}

/**
 * Returns the current temperature in degrees Celsius.
 * 
 * @return The temperature in degrees Celsius.
 */
float DHT11Controller::getTemperature()
{
    return _temperature;
}



float DHT11Controller::getHumidity()
{
    return _humidity;
/**
 * Returns the current humidity percentage.
 * 
 * @return The humidity percentage.
 */

}



/**
 * Returns the average temperature in degrees Celsius.
 * 
 * @return The average temperature in degrees Celsius.
 */
float DHT11Controller::getTemperatureAverage()
{
return _temperatureAverage;
}


/**
 * Returns the average humidity percentage.
 * 
 * @return The average humidity percentage.
 */
float DHT11Controller::getHumidityAverage()
{
    return _humidityAverage;
}

/**
 * Reads the current temperature and humidity values from the DHT11 sensor
 * and updates the internal stored values. The average temperature and humidity
 * values are also updated.
 */
void DHT11Controller::readTemperatureAndHumidity()
{
    _temperature = dht.readTemperature();
    _humidity = dht.readHumidity();
    this->averageTemperatureAndHumidityHandler();
}

/**
 * Updates the average temperature and humidity based on the recorded data.
 * It stores the current temperature and humidity in a circular buffer and 
 * calculates the average values by summing up the recorded entries. If an 
 * entry in the buffer is below a threshold, it calculates the average using 
 * the entries up to that point. Otherwise, it calculates the average across 
 * all entries in the buffer.
 */

void DHT11Controller::averageTemperatureAndHumidityHandler()
{
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