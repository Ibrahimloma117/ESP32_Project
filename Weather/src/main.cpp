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




