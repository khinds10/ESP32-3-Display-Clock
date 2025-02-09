#ifndef EXTENDED_WIFI_H
#define EXTENDED_WIFI_H

#include <WiFi.h>

class ExtendedWiFi {
private:
    const char* ssid;
    const char* password;

public:
    ExtendedWiFi(const char* wifi_ssid, const char* wifi_password) 
        : ssid(wifi_ssid), password(wifi_password) {}

    /**
     * Connect to a WiFi network
     */
    void init() {
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        Serial.print("Connecting to WiFi ..");
        while (WiFi.status() != WL_CONNECTED) {
            Serial.print('.');
            delay(1000);
        }
        Serial.println(WiFi.localIP());
    }

    String getIPAddress() {
        return WiFi.localIP().toString();
    }

    String getSSID() {
        return ssid;
    }

    String getPassword() {
        return password;
    }

    String getRSSI() {
        return String(WiFi.RSSI());
    }
};

#endif // EXTENDED_WIFI_H