#include "LcdController.h"

LcdController::LcdController() : LcdController(12, 11, 5, 4, 3, 2, 6) {}

/**
 * Constructor for LcdController that takes 7 arguments.
 * @param LCD_RS_pin Pin number for LCD RS
 * @param LCD_E_pin Pin number for LCD E
 * @param LCD_D4_pin Pin number for LCD D4
 * @param LCD_D5_pin Pin number for LCD D5
 * @param LCD_D6_pin Pin number for LCD D6
 * @param LCD_D7_pin Pin number for LCD D7
 * @param LCD_A_pin Pin number for LCD A (backlight)
 */
LcdController::LcdController(int LCD_RS_pin, int LCD_E_pin, int LCD_D4_pin, int LCD_D5_pin, int LCD_D6_pin, int LCD_D7_pin, int LCD_A_pin)
    : lcd(LCD_RS_pin, LCD_E_pin, LCD_D4_pin, LCD_D5_pin, LCD_D6_pin, LCD_D7_pin) {
    _lightUpPin = LCD_A_pin;
    pinMode(_lightUpPin, OUTPUT);
    changeLightUp();
    lcd.begin(16, 2);
}


/**
 * Prints a message to the LCD at the current line.
 * If clear is true, the display is cleared first.
 * @param text The message to be printed
 * @param clear Whether to clear the display before printing
 */
void LcdController::print(const char* text, bool clear) {
    if (clear) {
        lcd.clear();
    }
    lcd.setCursor(0, _line);
    lcd.print(text);
}

/**
 * Switches the current line of the LCD between 0 and 1.
 */
void LcdController::changeLine() {
    _line = (_line == 0) ? 1 : 0;
}


/**
 * Toggles the backlight of the LCD screen on and off.
 * Changes the state of the _lightUp flag and updates the
 * backlight pin accordingly.
 */

void LcdController::changeLightUp() {
    _lightUp = _lightUp ? false : true;
    digitalWrite(_lightUpPin, _lightUp ? HIGH : LOW);
}

/**
 * Displays the current temperature and humidity on the LCD
 * with a header [A] to indicate that it is actual data.
 * @param temp The current temperature
 * @param humidity The current humidity
 */
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

/**
 * Displays the current PM levels on the LCD with a header [A] to indicate
 * that it is actual data. If dataRead is false, it displays a message indicating
 * that it is waiting for data.
 * @param pm1 The current PM1 level
 * @param pm2 The current PM2.5 level
 * @param pm10 The current PM10 level
 * @param dataRead Whether the data is valid and ready to be displayed
 */
void LcdController::show_actual_pm(String pm1, String pm2, String pm10, bool dataRead) {
    if (dataRead) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[A]ug/m3 PM1:");
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

/**
 * Displays the long-term average temperature and humidity on the LCD with a
 * header [L] to indicate that it is long-term data.
 * @param temp The long-term average temperature
 * @param humidity The long-term average humidity
 */
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

/**
 * Displays the long-term average PM levels on the LCD with a header [L] to
 * indicate that it is long-term data. If dataRead is false, it displays a
 * message indicating that it is waiting for data.
 * @param pm1 The long-term average PM1 level
 * @param pm2 The long-term average PM2.5 level
 * @param pm10 The long-term average PM10 level
 * @param dataRead Whether the data is valid and ready to be displayed
 */
void LcdController::show_long_term_pm(String pm1, String pm2, String pm10, bool dataRead) {
    if (dataRead) {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[L]ug/m3 PM1:");
        lcd.print(pm1);
        lcd.setCursor(0, 1);
        lcd.print("PM2:");
        lcd.print(pm2);
        lcd.print(" PM10:");
        lcd.print(pm10);   
    } else {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("[L] PM: WAITING");
        lcd.setCursor(0, 1);
        lcd.print("FOR DATA...");
    }
}

/**
 * Displays a warning message on the LCD when air quality levels exceed a
 * certain threshold. The message is displayed until the user presses the
 * button again.
 */
void LcdController::show_warning() {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("!!!HIGH DUST!!!");
    lcd.setCursor(0, 1);
    lcd.print("!CONCENTRATION!");
}
