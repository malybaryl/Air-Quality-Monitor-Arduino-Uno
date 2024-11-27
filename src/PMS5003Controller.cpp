#include "PMS5003Controller.h"

// Domyślny konstruktor
PMS5003Controller::PMS5003Controller() : PMS5003Controller(10, 13) {}

// Konstruktor z parametrami
PMS5003Controller::PMS5003Controller(int PMS5003_RX_Pin, int PMS5003_TX_Pin)
    : pmsSerial(PMS5003_RX_Pin, PMS5003_TX_Pin), pms(pmsSerial) {
    pmsSerial.begin(9600); 
}

// Funkcja odczytu danych z czujnika
void PMS5003Controller::readPM() {
    if (readPMSdata(&pmsSerial)) {
        // reading data was successful!
        _PM1_0 = data.pm10_standard;
        _PM2_5 = data.pm25_standard;
        _PM10 = data.pm100_standard;
        this -> readPMAverage(); 
    }
}

void PMS5003Controller::readPMAverage() {
    dataLongTerm[0][dataIndex] = data.pm10_standard;
    dataLongTerm[1][dataIndex] = data.pm25_standard;
    dataLongTerm[2][dataIndex] = data.pm100_standard;
    dataIndex = (dataIndex + 1) % 25;
    float pm1_0_sum = 0;
    float pm2_5_sum = 0;
    float pm10_sum = 0;
    for (int i = 0; i < 25; i++){
        if (dataLongTerm[0][i] < 0.1 && dataLongTerm[1][i] <= 0.1){
            _PM1_0Average = pm1_0_sum / (i + 1);
            _PM2_5Average = pm2_5_sum / (i + 1);
            _PM10Average = pm10_sum / (i + 1);
            break;
        }
        pm1_0_sum += dataLongTerm[0][i];
        pm2_5_sum += dataLongTerm[1][i];
        pm10_sum += dataLongTerm[2][i];
        if (i == 24){
            _PM1_0Average = pm1_0_sum / 25;
            _PM2_5Average = pm2_5_sum / 25;
            _PM10Average = pm10_sum / 25;
        }
    }
}

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
 
  /* debugging
  for (uint8_t i=2; i<32; i++) {
    Serial.print("0x"); Serial.print(buffer[i], HEX); Serial.print(", ");
  }
  Serial.println();
  */
  
  // The data comes in endian'd, this solves it so it works on all platforms
  uint16_t buffer_u16[15];
  for (uint8_t i=0; i<15; i++) {
    buffer_u16[i] = buffer[2 + i*2 + 1];
    buffer_u16[i] += (buffer[2 + i*2] << 8);
  }
 
  // put it into a nice struct :)
  memcpy((void *)&data, (void *)buffer_u16, 30);
 
  if (sum != data.checksum) {
    return false;
  }
  // success!
  return true;
}
