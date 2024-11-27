#ifndef LCDCONTROLLER_H
#define LCDCONTROLLER_H

#include <Arduino.h> 
#include <LiquidCrystal.h>

class LcdController {
    LiquidCrystal lcd;  // Obiekt LCD jako pole klasy
    int _lightUpPin;
    bool _lightUp = false;
    int _line = 0;      // Bieżąca linia wyświetlacza

public:
    LcdController(); 
    LcdController(int LCD_RS_pin, int LCD_E_pin, int LCD_D4_pin, int LCD_D5_pin, int LCD_D6_pin, int LCD_D7_pin, int LCD_A_pin);
    void print(const char* text, bool clear = false);  // Wyświetlanie tekstu
    void changeLine();  // Zmiana linii wyświetlacza
    void changeLightUp();
    void clear() { lcd.clear(); }
    void show_actual_temperature_and_humidity(float temp, float humidity);
    void show_actual_pm(String pm1, String pm2, String pm10, bool dataRead);
    void show_long_term_temperature_and_humidity(float temp, float humidity);
    void show_long_term_pm();
    void show_warning();
};

#endif

