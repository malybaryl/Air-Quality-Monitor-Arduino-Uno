#include "PMS5003Controller.h"
#include "Delay.h"


PMS5003Controller::PMS5003Controller() : PMS5003Controller(10, 13) {}


/**
 * Constructor with pin assignment.
 * 
 * @param PMS5003_RX_Pin pin for SoftwareSerial RX
 * @param PMS5003_TX_Pin pin for SoftwareSerial TX
 */
PMS5003Controller::PMS5003Controller(int PMS5003_RX_Pin, int PMS5003_TX_Pin)
    : pmsSerial(PMS5003_RX_Pin, PMS5003_TX_Pin), pms(pmsSerial) {
    pmsSerial.begin(9600);
    pms.activeMode();
    pms.wakeUp(); 
}

/**
 * Requests and reads the data from the PMS5003 sensor.
 *
 * Sets the `PMS5003Controller` class' `_PM1_0`, `_PM2_5`, and `_PM10` fields to the
 * values of the immediately read data. If the data is successfully read,
 * calls `readPMAverage()`.
 *
 * @see readPMAverage()
 */
void PMS5003Controller::readPM() {
  
  pms.requestRead(); 
  if (readPMSdata(&pmsSerial)) 
  {  
    _PM1_0 =  data.pm10_env;
    _PM2_5 =  data.pm25_env;
    _PM10 =  data.pm100_env;
    this->readPMAverage(); 
  }

}

/**
 * Calculates the average of the PM1.0, PM2.5, and PM10 in the last 25 readings.
 *
 * The average is calculated by summing the values of the last 25 readings and
 * dividing by the number of samples.
 *
 * @see readPM()
 */
void PMS5003Controller::readPMAverage() {
    dataLongTerm[0][dataIndex] = data.pm10_env;
    dataLongTerm[1][dataIndex] = data.pm25_env;
    dataLongTerm[2][dataIndex] = data.pm100_env;

    dataIndex = (dataIndex + 1) % 25;

    int samplesCount = (dataIndex < 25 && dataLongTerm[0][dataIndex - 1] != 0) ? dataIndex : 25;

    float pm1_0_sum = 0;
    float pm2_5_sum = 0;
    float pm10_sum = 0;

    for (int i = 0; i < samplesCount; i++) {
        pm1_0_sum += dataLongTerm[0][i];
        pm2_5_sum += dataLongTerm[1][i];
        pm10_sum += dataLongTerm[2][i];
    }

    _PM1_0Average = pm1_0_sum / samplesCount;
    _PM2_5Average = pm2_5_sum / samplesCount;
    _PM10Average = pm10_sum / samplesCount;
}


/**
 * Reads data from the PMS5003 sensor stream and populates the `data` struct.
 *
 * This function attempts to read a data frame from the provided stream. It verifies
 * the presence of the start byte and ensures that a complete 32-byte frame is available.
 * The function checks the data integrity by calculating and verifying the checksum
 * against the data's checksum. If successful, the data is stored in the `data` struct.
 *
 * @param s Pointer to a Stream object from which data is read.
 * @return true if the data is successfully read and verified; false otherwise.
 */

bool PMS5003Controller::readPMSdata(Stream *s) {
    if (! s->available()) {
    return false;
  }
  
  // Read a byte at a time until we get to the special '0x42' start-byte
  if (s->peek() != 0x42) {
    s->read();
    return false;
  }

  // Now read all 32 bytes
  if (s->available() < 32) {
    return false;
  }
    
  uint8_t buffer[32];    
  uint16_t sum = 0;
  s->readBytes(buffer, 32);

  // get checksum ready
  for (uint8_t i=0; i<30; i++) {
    sum += buffer[i];
  }
  
  // The data comes in endian'd, this solves it so it works on all platforms
  uint16_t buffer_u16[15];
  for (uint8_t i=0; i<15; i++) {
    buffer_u16[i] = buffer[2 + i*2 + 1];
    buffer_u16[i] += (buffer[2 + i*2] << 8);
  }

  // put it into a nice struct :)
  memcpy((void *)&data, (void *)buffer_u16, 30);

  if (sum != data.checksum) {
    Serial.println("Checksum failure");
    return false;
  }
  // success!
  return true;
}

