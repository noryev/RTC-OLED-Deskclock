#include <Wire.h>
#include "RTClib.h"
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

RTC_DS3231 rtc;

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup()
{
    Serial.begin(57600);

#ifndef ESP8266
    while (!Serial)
        ; // wait for serial port to connect. Needed for native USB
#endif

    if (!rtc.begin())
    {
        Serial.println("Couldn't find RTC");
        Serial.flush();
        while (1)
            delay(10);
    }
    rtc.adjust(DateTime(2023, 6, 2, 11, 45, 0));
    if (rtc.lostPower())
    {
        Serial.println("RTC lost power, let's set the time!");
        rtc.adjust(DateTime(2023, 6, 2, 11, 44, 0));
    }

    // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
    { // Address 0x3C for 128x64
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    display.clearDisplay();
}

void loop()
{
    DateTime now = rtc.now();

    // Print to the Serial Monitor
    Serial.println(now.year(), DEC);
    Serial.print('/');
    Serial.print(now.month(), DEC);
    Serial.print('/');
    Serial.print(now.day(), DEC);
    Serial.print(" (");
    Serial.print(daysOfTheWeek[now.dayOfTheWeek()]);
    Serial.print(") ");
    Serial.print(now.hour(), DEC);
    Serial.print(':');
    Serial.print(now.minute(), DEC);
    Serial.print(':');
    Serial.print(now.second(), DEC);
    Serial.println();

    Serial.print("Temperature: ");
    Serial.print(rtc.getTemperature());
    Serial.println(" C");
    Serial.println();

    // Print to the SSD1306 display
    display.clearDisplay();
    display.setTextSize(1); // Set text size to 1
    display.setTextColor(WHITE);

    // Draw progress bar
    int progress = (int)((now.second() / 59.0) * SCREEN_WIDTH);
    display.drawRect(0, 0, SCREEN_WIDTH, 8, WHITE); // Draw border at the top of the screen
    display.fillRect(2, 2, progress, 4, WHITE);     // Draw progress

    display.setCursor(0, 16); // Move cursor down for the text

    display.println(now.year(), DEC);
    display.print('/');
    display.print(now.month(), DEC);
    display.print('/');
    display.print(now.day(), DEC);
    display.print(" (");
    display.print(daysOfTheWeek[now.dayOfTheWeek()]);
    display.println(") ");

    display.setTextSize(2); // Set text size to 2 for the time
    if (now.hour() < 10)
        display.print('0');
    display.print(now.hour(), DEC);
    display.print(':');
    if (now.minute() < 10)
        display.print('0');
    display.print(now.minute(), DEC);
    display.print(':');
    if (now.second() < 10)
        display.print('0');
    display.println(now.second(), DEC);

    display.setTextSize(1); // Set the text size back to 1 for the temperature display
    display.print("Temp: ");
    display.print(rtc.getTemperature());
    display.println(" C");

    display.display();

    delay(1000); // Change delay to 1000 milliseconds
}
// Add a accurate temp/hummidity/air-pressure/air-quality senser ASAP!

// Check OLED in a few days- maybe switch to a long lasting LCD to reduce display degradation