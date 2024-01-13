# RTC-OLED-Deskclock

This project involves creating a desk clock using an Arduino Uno, a DS3231 Real-Time Clock (RTC) module, and a SSD1306 OLED display. 

More information located here: [Adafruit DS321 RTC](https://learn.adafruit.com/adafruit-ds3231-precision-rtc-breakout/arduino-usage)

SDA pin goes to A4 and SCL goes to A5 to Arduion Uno pins
## Hardware

1. Arduino Uno
2. DS3231 RTC Module
3. SSD1306 OLED Display

## Steps

### 1. Hardware Selection

Chose the Arduino Uno as the microcontroller, a DS3231 RTC for keeping accurate time, and a SSD1306 OLED for visualization.

### 2. Initial Setup and Testing

Wired up the RTC module to the Arduino and verified its operation. The RTClib library was used for interfacing with the RTC module. The Arduino was programmed to initialize the RTC and print the current date and time to the Serial Monitor. If the RTC was not initialized or lost power, the program would set it to a specific date and time.

### 3. Integrating the OLED Display

Once the RTC module was confirmed to be working, the SSD1306 OLED display was added. The Adafruit SSD1306 library was used for this purpose. Code was written to print the current date, time, and temperature (read from the RTC module) to the OLED display.

### 4. Adding Visual Features

To better utilize the OLED display, a progress bar was added that would fill up over each minute. Code was written to calculate how full the progress bar should be based on the current second, and then draw it on the display.

### 5. Fine-Tuning the Display

Adjustments were made to the OLED screen layout, such as changing the text size for the time display and reformatting the screen to have the progress bar at the top and the text at the bottom.

### 6. Setting the Correct Time

With the clock functioning as expected, the RTC module was set to the correct time. This was done with a line of code in the `setup()` function. After setting the time once, this line of code should be commented out or removed, as the RTC module will continue to keep time accurately on its own.

## Summary

This project involved creating a desk clock with an Arduino Uno, DS3231 RTC, and SSD1306 OLED display. The clock displays the current date, time, and temperature and includes a progress bar that visually represents the progress of each minute.

Remember setting the time is a bitch, first set the time of the board on the device by adding this string into the code on top of the lost power adjustment. So when doing this again, remember, first add this string:  rtc.adjust(DateTime(2023, 6, 3, 1, 14, 0)); below the lost power adjustment field. Then take the string back out and reflash the code and the rtc will then be synced up. If you leave the rtc.adjust string, it will keep setting the board to that set time instead of doing the math to add up the time like it should. Its not about setting the time everytime the board powers on, its about keeping track of the total time in general.
