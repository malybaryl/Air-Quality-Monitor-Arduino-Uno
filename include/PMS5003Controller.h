#ifndef PMS5003CONTROLLER_H
#define PMS5003CONTROLLER_H

#include "PMS.h"
#include "SoftwareSerial.h"

class PMS5003Controller {
    SoftwareSerial pmsSerial;
    PMS pms;
    PMS::DATA data;
    float _PM1_0;
    float _PM2_5;
    float _PM10;

public:
    PMS5003Controller();
    PMS5003Controller(int PMS5003_RX_Pin, int PMS5003_TX_Pin);
    float getPM1_0() { return _PM1_0; };
    float getPM2_5() { return _PM2_5; };
    float getPM10() { return _PM10; };
    void wakeUp() { pms.wakeUp(); };
    bool checkData() { return _PM1_0 > 0 || _PM2_5 > 0 || _PM10 > 0; };
    String getPM1_0String() { return String((int)_PM1_0); }
    String getPM2_5String() { return String((int)_PM2_5); }
    String getPM10String() { return String((int)_PM10); }
    void readPM();
};

#endif
