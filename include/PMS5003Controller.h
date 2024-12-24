#ifndef PMS5003CONTROLLER_H
#define PMS5003CONTROLLER_H

#include "PMS.h"
#include "SoftwareSerial.h"

class PMS5003Controller {
    SoftwareSerial pmsSerial;
    PMS pms;
    float _PM1_0;
    float _PM2_5;
    float _PM10;
    float _PM1_0Average;
    float _PM2_5Average;
    float _PM10Average;
    float dataLongTerm[3][25] = {0};
    int dataIndex = 0;
    struct pms5003data {
    uint16_t framelen;
    uint16_t pm10_standard, pm25_standard, pm100_standard;
    uint16_t pm10_env, pm25_env, pm100_env;
    uint16_t particles_03um, particles_05um, particles_10um, particles_25um, particles_50um, particles_100um;
    uint16_t unused;
    uint16_t checksum;
    };

    struct pms5003data data;

public:

    PMS5003Controller();
    PMS5003Controller(int PMS5003_RX_Pin, int PMS5003_TX_Pin);
    float getPM1_0() { return _PM1_0; };
    float getPM2_5() { return _PM2_5; };
    float getPM10() { return _PM10; };
    void wakeUp() { pms.wakeUp(); };
    void setPassiveMode() { pms.passiveMode(); };
    void requestRead() { pms.requestRead(); };
    bool hasValidData() { return (_PM1_0 >= 0 && _PM1_0 <= 1000) && (_PM2_5 >= 0 && _PM2_5 <= 1000) && (_PM10 >= 0 && _PM10 <= 1000);};
    String getPM1_0String() { return String((int)_PM1_0); }
    String getPM2_5String() { return String((int)_PM2_5); }
    String getPM10String() { return String((int)_PM10); }
    String getPM1_0AverageString() { return String((int)_PM1_0Average); }
    String getPM2_5AverageString() { return String((int)_PM2_5Average); }
    String getPM10AverageString() { return String((int)_PM10Average); }
    bool warning() { return (_PM1_0 > 20 || _PM2_5 > 25 || _PM10 > 50) || (_PM1_0Average > 20 || _PM2_5Average > 25 || _PM10Average > 50); }
    bool readPMSdata(Stream *s);
    void readPM();
    void readPMAverage();
};

#endif
