#include <LiquidCrystal.h>
#include <DHT.h>
#include <SoftwareSerial.h>

// Konfiguracja LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // RS, E, D4, D5, D6, D7

// Konfiguracja DHT11
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Konfiguracja PMS5003
SoftwareSerial pmsSerial(10, 13); // RX, TX

// Konfiguracja buzzera i przycisku
#define BUZZER_PIN 8
#define BUTTON_PIN 7

// Zmienne globalne
bool alert = false;                 // Flaga stanu alarmu
bool displayLongTerm = false;       // Flaga trybu wyświetlania
unsigned long lastUpdate = 0;       // Ostatni czas aktualizacji danych
const unsigned long updateInterval = 5000; // Interwał aktualizacji (5 sek.)

struct PMData {
  int pm1_0;
  int pm2_5;
  int pm10;
};

// Funkcje
PMData readPMS5003();
void displayData(float temp, float humidity, PMData pm);
void displayAlert();

void setup() {
  // Inicjalizacja LCD
  lcd.begin(16, 2);
  lcd.clear(); // Czyszczenie ekranu na starcie
  lcd.print("Inicjalizacja...");
  delay(2000);

  // Inicjalizacja DHT
  dht.begin();

  // Inicjalizacja PMS5003
  pmsSerial.begin(9600);

  // Konfiguracja pinów
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
}

void loop() {
  // Odczyt danych co updateInterval
  if (millis() - lastUpdate > updateInterval) {
    lastUpdate = millis();

    // Odczyt danych z czujników
    float temperature = dht.readTemperature();
    float humidity = dht.readHumidity();
    PMData pm = readPMS5003();

    // Analiza danych
    alert = (pm.pm2_5 > 50 || pm.pm10 > 80);

    // Wyświetlanie danych lub alertu
    if (alert) {
      digitalWrite(BUZZER_PIN, HIGH);
      displayAlert();
    } else {
      digitalWrite(BUZZER_PIN, LOW);
      displayData(temperature, humidity, pm);
    }
  }

  // Obsługa przycisku
  if (digitalRead(BUTTON_PIN) == LOW) {
    delay(200); // Debounce
    displayLongTerm = !displayLongTerm; // Zmiana trybu wyświetlania
    lcd.clear(); // Czyszczenie ekranu przy zmianie trybu
  }
}

// Funkcja odczytu danych z PMS5003
PMData readPMS5003() {
  PMData data = {0, 0, 0};

  // Sprawdź, czy dostępne są dane
  if (pmsSerial.available() >= 32) {
    byte buffer[32];
    if (pmsSerial.read() == 0x42 && pmsSerial.read() == 0x4D) { // Nagłówek
      pmsSerial.readBytes(buffer, 30);

      // Sprawdzenie sumy kontrolnej
      unsigned int checksum = 0x42 + 0x4D;
      for (int i = 0; i < 28; i++) {
        checksum += buffer[i];
      }
      unsigned int receivedChecksum = (buffer[28] << 8) | buffer[29];
      if (checksum == receivedChecksum) {
        data.pm1_0 = (buffer[10] << 8) | buffer[11];
        data.pm2_5 = (buffer[12] << 8) | buffer[13];
        data.pm10  = (buffer[14] << 8) | buffer[15];
      }
    }
  }

  return data;
}

// Funkcja wyświetlania danych
void displayData(float temp, float humidity, PMData pm) {
  lcd.setCursor(0, 0);
  if (displayLongTerm) {
    // Tryb długoterminowy
    lcd.print("D PM2.5:");
    lcd.print(pm.pm2_5);
    lcd.print(" ");
    lcd.setCursor(0, 1);
    lcd.print("PM10:");
    lcd.print(pm.pm10);
    lcd.print("  ");
  } else {
    // Tryb aktualny
    lcd.print("A T:");
    lcd.print(temp, 1);
    lcd.print("C H:");
    lcd.print(humidity, 1);
    lcd.setCursor(0, 1);
    lcd.print("PM2.5:");
    lcd.print(pm.pm2_5);
    lcd.print("  ");
  }
}

// Funkcja wyświetlania alertu
void displayAlert() {
  lcd.setCursor(0, 0);
  lcd.print("! UWAGA: ZAPYL !");
  lcd.setCursor(0, 1);
  lcd.print("PM2.5/PM10 HIGH");
}
