#ifndef DHT22_H
#define DHT22_H

#include <Arduino.h>
#include <DHT.h>
#include <DHT_U.h>
#include "config.h"

class ExtendedDHT22 {
private:
    DHT dht;
    uint8_t _pin;  // Store the pin number for debugging
    
    float celciusToFahrenheit(float celsius) {
        return (celsius * 9.0 / 5.0 + 32.0);
    }

public:
    ExtendedDHT22(uint8_t pin, uint8_t type) : dht(pin, type), _pin(pin) {}
    
    void begin() {
        dht.begin();
        Serial.print("DHT22 Initialized on pin: ");
        Serial.println(_pin);
    }

    String getTemperatureF() {
        float tempC = dht.readTemperature();
        if (isnan(tempC)) {
            Serial.print("Failed to read temperature from DHT22 on pin ");
            Serial.println(_pin);
            return "ERR";
        }
        float tempF = celciusToFahrenheit(tempC);
        return String(tempF, 0);
    }

    String getHumidity() {
        float h = dht.readHumidity();
        if (isnan(h)) {
            Serial.print("Failed to read humidity from DHT22 on pin ");
            Serial.println(_pin);
            return "ERR";
        }        
        return String(h, 0);
    }

    float getRawTemperatureF() {
        float tempC = dht.readTemperature();
        if (isnan(tempC)) return NAN;
        return celciusToFahrenheit(tempC);
    }

    float getRawHumidity() {
        return dht.readHumidity();
    }
};

#endif // DHT22_H