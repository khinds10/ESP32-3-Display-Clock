#ifndef CONFIG_H
#define CONFIG_H

// Add timezone
#define TIME_ZONE -5 // EST (UTC-5)
#define DST_OFFSET 1 // Add 1 hour during DST

// Display brightness settings (0-7)
#define TIME_DISPLAY_BRIGHTNESS 3
#define INSIDE_TEMP_BRIGHTNESS 1
#define OUTSIDE_TEMP_BRIGHTNESS 1

// First display
#define CLK1 22 // First display CLK
#define DIO1 23 // First display DIO

// Second display
#define CLK2 19 // Second display CLK
#define DIO2 21 // Second display DIO

// Third display
#define CLK3 32 // Third display CLK
#define DIO3 25 // Third display DIO

// DHT22 pin
#define DHTPIN 18
#define DHTTYPE DHT22

// Add temperature offset correction
#define TEMP_OFFSET 0.0 // Add 3 degrees to compensate for sensor

// WiFi credentials
const char* ssid = "LINKSYS";
const char* password = "password";
char date_string[100];

// // NTP setup
const char* ntpServer = "north-america.pool.ntp.org";
const long  gmtOffset_sec = -18000; // Eastern Daylight Time (EDT)
const int   daylightOffset_sec = 3600;

// scheduled datahub config
const char* datahub_host = "https://devices.website.net";

// weather api endpoint
const char* weather_api_endpoint = "https://openweather.website.net/";
const char* device_name = "temp-check-default";
const char* zipcode = "10001";

// latitude and logitude
float latitude = 40.0;
float longitude = -70.0;

// Update intervals
const unsigned long WEATHER_UPDATE_INTERVAL = 60000; // 60 seconds

#endif // CONFIG_H 