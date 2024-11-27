#include "LcdController.h"

// Konstruktor domyślny deleguje do drugiego konstruktora
LcdController::LcdController() : LcdController(12, 11, 5, 4, 3, 2, 6) {}

// Konstruktor z parametrami i inicjalizacją LiquidCrystal
LcdController::LcdController(int LCD_RS_pin, int LCD_E_pin, int LCD_D4_pin, int LCD_D5_pin, int LCD_D6_pin, int LCD_D7_pin, int LCD_A_pin)
    : lcd(LCD_RS_pin, LCD_E_pin, LCD_D4_pin, LCD_D5_pin, LCD_D6_pin, LCD_D7_pin) {
    _lightUpPin = LCD_A_pin;
    pinMode(_lightUpPin, OUTPUT);
    changeLightUp();
    lcd.begin(16, 2);
}

// Implementacja metody print
void LcdController::print(const char* text, bool clear) {
    if (clear) {
        lcd.clear();
    }
    lcd.setCursor(0, _line);
    lcd.print(text);
}

// Implementacja metody changeLine
void LcdController::changeLine() {
    _line = (_line == 0) ? 1 : 0;
}


void LcdController::changeLightUp() {
    _lightUp = _lightUp ? false : true;
    digitalWrite(_lightUpPin, _lightUp ? HIGH : LOW);
}

void LcdController::show_actual_temperature_and_humidity(float temp, float humidity) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("[A] Temp: ");
    lcd.print(temp);
    lcd.setCursor(14,0);
    lcd.print(" C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.setCursor(14,1);
    lcd.print(" %");
}

void LcdController::show_actual_pm(String pm1, String pm2, String pm10, bool dataRead) {
    if (dataRead) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[A]      PM1:");
        lcd.print(pm1);
        lcd.setCursor(0, 1);
        lcd.print("PM2:");
        lcd.print(pm2);
        lcd.print(" PM10:");
        lcd.print(pm10);   
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[A] PM: WAITING");
        lcd.setCursor(0, 1);
        lcd.print("FOR DATA...");
    }
}

void LcdController::show_long_term_temperature_and_humidity(float temp, float humidity) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("[L] Temp: ");
    lcd.print(temp);
    lcd.setCursor(14,0);
    lcd.print(" C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.setCursor(14,1);
    lcd.print(" %");
}

void LcdController::show_long_term_pm() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("[L]     PM1: 22");
    lcd.setCursor(0, 1);
    lcd.print("PM2: 22 PM10: 22");
}

void LcdController::show_warning() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("!!!HIGH DUST!!!");
    lcd.setCursor(0, 1);
    lcd.print("!CONCENTRATION!");
}
