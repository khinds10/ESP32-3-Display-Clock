# ESP32 Time and Temperature Display

This project uses an ESP32 microcontroller to display the current time and temperatures on three TM1637 displays. The first display shows the current time in 12-hour format with a blinking colon and PM indicator. The second display shows the indoor temperature from a DHT22 sensor. The third display shows the outdoor temperature fetched from an online weather API.







DHT 22
    -    -> GND
    +    -> VIN
    DATA -> D18

TIME
    GND  -> GND
    5V   -> VIN
    DIO  -> D23
    CLK  -> D22
    
OUTDOOR TEMP
    GND  -> GND
    5V   -> VIN
    DIO  -> D25
    CLK  -> D32
    
INDOOR TEMP
    GND  -> GND
    5V   -> VIN
    DIO  -> D21
    CLK  -> D19













## Hardware Setup

### Components Required

- 1 x ESP32 Development Board
- 3 x TM1637 4-Digit 7-Segment Displays
- 1 x DHT22 Temperature and Humidity Sensor
- Jumper wires
- Breadboard (optional)

### Wiring Diagram

#### TM1637 Displays

- **Display 1 (Time)**
  - CLK1: GPIO 22
  - DIO1: GPIO 23

- **Display 2 (Indoor Temperature)**
  - CLK2: GPIO 19
  - DIO2: GPIO 21

- **Display 3 (Outdoor Temperature)**
  - CLK3: GPIO 32
  - DIO3: GPIO 25

#### DHT22 Sensor

- VCC: 3.3V or 5V
- GND: Ground
- Data: GPIO 18

### Notes

- Ensure all components share a common ground with the ESP32.
- Use appropriate pull-up resistors if necessary for the DHT22 data line.

## Software Setup

### Prerequisites

- [PlatformIO](https://platformio.org/) installed on your development environment.
- An internet connection for the ESP32 to fetch weather data.

### Configuration

1. **Copy Configuration File**

   Copy `src/config_shadow.h` to `src/config.h` and replace the placeholder values with your actual WiFi credentials and any other necessary configuration.

   ```bash
   cp src/config_shadow.h src/config.h
   ```

2. **Edit `config.h`**

   Open `src/config.h` and update the following values:

   ```cpp
   // WiFi credentials
   const char* WIFI_SSID = "Your_WiFi_SSID";
   const char* WIFI_PASSWORD = "Your_WiFi_Password";

   // Weather API
   const char* WEATHER_API_URL = "https:// OPENWEATHER API URL /";

   // Update intervals
   const unsigned long WEATHER_UPDATE_INTERVAL = 6000; // 60 seconds
   ```

### Building and Uploading

1. Connect your ESP32 to your computer via USB.
2. Open the project in your PlatformIO environment.
3. Build and upload the firmware to the ESP32.

### License

This project is licensed under the GNU General Public License v3.0. See the [LICENSE](https://www.gnu.org/licenses/gpl-3.0.en.html) file for details.

### Author

- **Kevin Hinds**
- Website: [www.kevinhinds.com](http://www.kevinhinds.com)
- Date: 2025-01-28 

## GNU General Public License

This program is free software: you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with this program. If not, see [https://www.gnu.org/licenses/](https://www.gnu.org/licenses/). 