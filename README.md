# Air Quality Monitor Arduino Uno

A real-time air quality monitoring system using Arduino Uno Rev3. This project measures particulate matter (PM1.0, PM2.5, PM10), temperature, and humidity. The data is displayed on a 16x2 LCD screen and analyzed to provide long-term insights. Alerts are triggered via a buzzer when air quality exceeds safe thresholds.

---

## Features
- **Air Quality Monitoring**: Measures PM1.0, PM2.5, and PM10 levels using the PMS5003 sensor.
- **Environmental Data**: Reads temperature and humidity with the DHT11 sensor.
- **Visual Feedback**: Displays real-time data and long-term analysis on a 16x2 LCD screen.
- **Audible Alert**: Triggers a buzzer if particulate levels exceed safety thresholds.
- **User Interaction**: Toggle between real-time and historical data using a tactile push button.

---

## Components
1. **Arduino Uno Rev3** - Microcontroller board.
2. **PMS5003** - Particulate matter sensor for PM1.0, PM2.5, and PM10.
3. **DHT11** - Temperature and humidity sensor.
4. **16x2 LCD Display** - Blue backlit display with parallel interface.
5. **Buzzer** - 5V buzzer with built-in driver.
6. **Tactile Push Button** - User input for toggling display modes.
7. **Power Supply** - 12V/2.5A adapter.

---

## How It Works
1. The system collects air quality and environmental data every 5 minutes.
2. Data is analyzed to determine real-time air conditions and stored for long-term analysis.
3. A push button allows users to switch between real-time data and historical analysis views.
4. If PM levels exceed safe thresholds, the system triggers a buzzer and displays an alert message on the LCD.
5. The buzzer can be silenced by pressing the button.

---

## Setup and Connections
### Wiring Diagram
| Component         | Arduino Pin     | Notes                              |
|-------------------|-----------------|------------------------------------|
| PMS5003 TX        | D10             | Particulate matter sensor TX line |
| PMS5003 RX        | D13             | Particulate matter sensor RX line |
| DHT11 Data        | D9              | Data line for temperature & humidity |
| LCD RS            | D12             | LCD control pin                   |
| LCD E             | D11             | LCD enable pin                    |
| LCD D4-D7         | D5-D2           | LCD data pins                     |
| Buzzer            | D8              | + connected to D8, - to GND       |
| Button            | D7              | Connected with 10kΩ pull-up       |
| LCD Backlight A   | D6              | Anode                             |
| LCD Backlight K   | GND             | Cathode                           |

---

## Installation
1. Connect all components according to the wiring diagram.
2. Upload the provided Arduino code to your Arduino Uno using the Arduino IDE.
3. Adjust the contrast of the LCD using the potentiometer for optimal display clarity.

---

## Usage
- **Start-Up**: The system initializes and displays real-time data.
- **Toggle Views**: Press the button to switch between:
  - **Real-Time Data**: Current air quality, temperature, and humidity.
  - **Historical Data**: Long-term averages and trends.
- **Alerts**: When PM levels exceed safe thresholds:
  - A warning message appears on the LCD.
  - The buzzer sounds until silenced with the button.

---

## License
This project is open-source and available under the MIT License.

---

## Acknowledgments
Special thanks to the Arduino community and open-source libraries for enabling this project.
