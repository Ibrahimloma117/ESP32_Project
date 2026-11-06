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
#define LCD_SDA      17 //MOSI
#define LCD_SCL      18 //SCK

//BMP280 I2C
#define BMP280_ADDRESS 0x76
#define SDA 8
#define SCL 9
// CBB - 3v3 for I2C
// SD0 > GND - selects I2C address (0x76 or 0x77)

//joystick
#define joy_x 1
#define joy_y 2
#define joy_sw 7

bool sensorOK = false;

Adafruit_ST7789 tft = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);
Adafruit_BMP280 bmp; // I2C

void setup() {
    Serial.begin(115200);
    Serial.println("ST7789 TFT Test");

    SPI.begin(LCD_SCL, -1, LCD_SDA, LCD_CS);
    tft.init(240, 320); 
    tft.setRotation(0); 
    tft.fillScreen(ST77XX_BLUE);
    delay(1000);

    Wire.begin(SDA, SCL);
    sensorOK = bmp.begin(BMP280_ADDRESS);

    if (!sensorOK) {
        tft.setTextColor(ST77XX_RED);
        tft.setTextSize(2);
        tft.setCursor(10, 10);
        tft.println("BMP280 ERROR");
    }



}

void loop() {
    if(sensorOK) {
        double temp = bmp.readTemperature();

        tft.fillRect(0, 120, 240, 40, ST77XX_BLUE); // Clear previous temperature display


        tft.setTextSize(3);
        tft.setTextColor(ST77XX_CYAN);
        tft.setCursor(25, 90);
        tft.print("Temperature");


        // Display temperature on the screen
        tft.setTextSize(4);
        tft.setTextColor(ST77XX_WHITE);
        tft.setCursor(25, 130);
        tft.print(temp, 2); // Print temperature with 1 decimal place
        tft.print(" C");
    }
    delay(1000); // Update every second
}


