#include "PMS5003Controller.h"

// Domyślny konstruktor
PMS5003Controller::PMS5003Controller() : PMS5003Controller(10, 13) {}

// Konstruktor z parametrami
PMS5003Controller::PMS5003Controller(int PMS5003_RX_Pin, int PMS5003_TX_Pin)
    : pmsSerial(PMS5003_RX_Pin, PMS5003_TX_Pin), pms(pmsSerial) {
    pmsSerial.begin(9600); 
    pms.activeMode();
    pms.wakeUp();
}

// Funkcja odczytu danych z czujnika
void PMS5003Controller::readPM() {
    if (pms.read(data)) {
        _PM1_0 = data.PM_AE_UG_1_0;
        _PM2_5 = data.PM_AE_UG_2_5;
        _PM10 = data.PM_AE_UG_10_0;
    }
}
