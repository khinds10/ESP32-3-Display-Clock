#ifndef TM1637_H
#define TM1637_H

#include <Arduino.h>
#include <TM1637Display.h>
#include <time.h>

class ExtendedTM1637Display : public TM1637Display {
private:
    unsigned long lastToggle = 0;
    bool colonOn = false;
    const uint8_t FAHRENHEIT_SYMBOL = SEG_A | SEG_F | SEG_E | SEG_G; // F symbol

public:
    ExtendedTM1637Display(uint8_t clkPin, uint8_t dataPin) : TM1637Display(clkPin, dataPin) {}
    
    void updateTimeDisplay(struct tm* timeInfo) {

        // Convert to 12-hour format
        int hours = timeInfo->tm_hour;
        bool isPM = hours >= 12;
        hours = hours % 12;
        
        // Convert 0 to 12 for midnight
        if (hours == 0) hours = 12;
        int minutes = timeInfo->tm_min;

        // Update time display with blinking colon and PM indicator
        if (millis() - lastToggle >= 500) {
            lastToggle = millis();
            colonOn = !colonOn;
            uint8_t dots = (colonOn ? 0x40 : 0x00) | (isPM ? 0x80 : 0x00); // Combine colon and PM dot
            this->showNumberDecEx(hours * 100 + minutes, dots, true);
        }
    }

    void showTemperature(String tempStr) {
        
        // Convert String to float, then to rounded int
        float tempFloat = tempStr.toFloat();
        int temp = (int)round(tempFloat);
        
        // Display temperature as two digits with F symbol
        uint8_t data[] = {
            0,
            this->encodeDigit(temp / 10),
            this->encodeDigit(temp % 10),
            FAHRENHEIT_SYMBOL
        };
        this->setSegments(data);
    }
};

#endif // TM1637_H