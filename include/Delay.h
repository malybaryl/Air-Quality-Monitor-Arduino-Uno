#ifndef DELAY_H
#define DELAY_H
#include <Arduino.h>

class Delay {
public:
    static void delay_ms(int ms) {
        delay(ms);
    }
};

#endif