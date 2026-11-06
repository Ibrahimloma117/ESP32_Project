#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>

#include <Wire.h>
#include <Adafruit_BMP280.h> 

//LCD 
#define LCD_CS       4
#define LCD_DC       5
#define LCD_RST      6
#define LCD_SDA      17
#define LCD_SCL      18

//BMP280 I2C
#define BMP280_ADDRESS 0x76
#define SDA 9
#define SCL 8
// CBB - 3v3 for I2C
// SD0 > GND - selects I2C address (0x76 or 0x77)

Adafruit_ST7789 tft = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);

void setup() {
    Serial.begin(115200);
    SPI.begin(LCD_SCL, -1, LCD_SDA, LCD_RST);
    Serial.println("ST7789 TFT Test");

    tft.init(240, 320); // Init ST7789 240x320 7
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(3);
    tft.setCursor(10, 10); // Set cursor position
    tft.println("Hello, World!");

}

void loop() {
    // Nothing to do here
}


