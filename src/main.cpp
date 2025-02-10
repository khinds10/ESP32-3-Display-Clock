/**
 * Time and Temperature Display Program
 *
 * This program is designed to run on an ESP32 microcontroller. It connects to a WiFi network,
 * fetches the current time and weather data, and displays the time and temperatures on three
 * TM1637 displays. The first display shows the current time in 12-hour format with a blinking
 * colon and PM indicator. The second display shows the indoor temperature from a DHT22 sensor.
 * The third display shows the outdoor temperature fetched from an online weather API.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 *
 * Author: Kevin Hinds
 * Date: 2025-01-28
 * Website: www.kevinhinds.com
 */

#include <Adafruit_Sensor.h>
#include <Arduino.h>
#include <ArduinoJson.h>
#include "config.h"
#include <string>
#include <time.h>
#include <WiFi.h>
#include <Wire.h>
#include <HTTPClient.h>

// include internet files
#include <internet/api.h>
#include <internet/wifi.h>

// include device files
#include <DHT.h>
#include <DHT_U.h>
#include <devices/dht22.h>
#include <devices/LoopManager.h>

// include display files
#include <TM1637Display.h>
#include <devices/TM1637.h>

// Create objects
ExtendedTM1637Display timeDisplay(CLK1, DIO1);        // time display
ExtendedTM1637Display insideTempDisplay(CLK2, DIO2);  // inside temp display
ExtendedTM1637Display outsideTempDisplay(CLK3, DIO3); // outside temp display

// DHT22 sensor
ExtendedDHT22 dht(DHTPIN, DHTTYPE);

// API
API api;

// WiFi
ExtendedWiFi wifi(ssid, password);

// LoopManager for API incremental updates and restart thresholds
LoopManager loopManager;

void setup() {
  Serial.begin(115200);

  // begin WiFi connection
  wifi.init();
  Serial.print("RSSI: ");
  Serial.println(wifi.getRSSI());

  // init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);

  // time display
  timeDisplay.setBrightness(TIME_DISPLAY_BRIGHTNESS);
  timeDisplay.clear();

  // inside temp display
  insideTempDisplay.setBrightness(INSIDE_TEMP_BRIGHTNESS);
  insideTempDisplay.clear();

  // outside temp display
  outsideTempDisplay.setBrightness(OUTSIDE_TEMP_BRIGHTNESS);
  outsideTempDisplay.clear();

  // Get initial outside temperature reading
  dht.begin();
  String outsideTemp = api.updateWeatherHub(dht.getTemperatureF(), dht.getHumidity());
  outsideTempDisplay.showTemperature(outsideTemp);
}

void loop() {

    loopManager.increment();
    Serial.println("Samples taken: " + String(loopManager.getSamplesTaken()));
    Serial.println("Total samples: " + String(loopManager.getTotalSamples()));

    // Get current time
    time_t now = time(nullptr);
    struct tm *timeInfo = localtime(&now);
    timeDisplay.updateTimeDisplay(timeInfo);

    // Display inside temperature
    insideTempDisplay.showTemperature(dht.getTemperatureF());

    // Update the weather hub, data hub, and outside temperature display
    if (loopManager.shouldUpdateAPI()) {
        String outsideTemp = api.updateWeatherHub(dht.getTemperatureF(), dht.getHumidity());
        outsideTempDisplay.showTemperature(outsideTemp);
        loopManager.resetSamplesTaken();
    }

    // Restart the ESP32
    if (loopManager.shouldRestart()) ESP.restart();
    delay(1000);
}