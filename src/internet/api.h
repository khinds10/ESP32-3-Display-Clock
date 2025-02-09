#ifndef API_H
#define API_H

#include <Arduino.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include "config.h"

class API {
private:
    String floatToString(float f) {
        return String(f, 0);
    }

public:
    API() {}

    /**
     * update the weather hub with the current temperature and humidity
     * @param String currentTemperature
     * @param String currentHumidity
     */
    String updateWeatherHub(String temperature, String humidity) {
        HTTPClient http;
        String requestBody;
        
        DynamicJsonDocument weatherResponseDoc(40000);
        StaticJsonDocument<1000> deviceHubPOSTDoc;
        
        // get the outside weather
        String url = String(weather_api_endpoint) + "?lat=" + String(latitude) + "&lon=" + String(longitude) + "&units=imperial";
        http.begin(url);
        http.addHeader("Content-Type", "application/json"); 
        int httpCode = http.GET();
        
        if(httpCode == HTTP_CODE_OK) {  
            String payload = http.getString();
            Serial.println("Weather response: " + payload);
            
            // Parse the JSON response
            DeserializationError error = deserializeJson(weatherResponseDoc, payload);
            if (error) {
                Serial.print("deserializeJson() failed: ");
                Serial.println(error.c_str());
            }
        }
        http.end();

        // create JSON document including the inside and outside conditions
        deviceHubPOSTDoc["device"] = device_name;
        deviceHubPOSTDoc["value1"] = temperature;  // indoor temperature
        deviceHubPOSTDoc["value2"] = humidity;     // indoor humidity
        deviceHubPOSTDoc["value3"] = String(weatherResponseDoc["current"]["temp"].as<float>());      // outdoor temperature
        deviceHubPOSTDoc["value4"] = String(weatherResponseDoc["current"]["humidity"].as<int>());    // outdoor humidity
        deviceHubPOSTDoc["value5"] = weatherResponseDoc["current"]["weather"][0]["description"].as<const char*>();  // weather description
        
        serializeJsonPretty(deviceHubPOSTDoc, requestBody);
        Serial.println(requestBody);

        http.begin((String) datahub_host + "/api/logJSON/");
        http.addHeader("Content-Type", "application/json");
        httpCode = http.PUT(requestBody);
        Serial.println(httpCode);
        Serial.println(http.getString());
        http.end();
        return String(weatherResponseDoc["current"]["temp"].as<float>());
    }
};

#endif // API_H
