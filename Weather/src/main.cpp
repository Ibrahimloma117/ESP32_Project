#include <Arduino.h>
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789
#include <SPI.h>
#include<pages.h> // custom library

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
bool lastButton = HIGH;
int page = 0; // home = 0, Temp = 1, Press = 2
Adafruit_ST7789 tft = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);
Adafruit_BMP280 bmp; 
uint32_t Time, oldTime = 0;
String name;

int selectBox = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("Weather Station Starting...");
    pinMode(joy_sw, INPUT_PULLUP);
    analogReadResolution(12); // 12bits, 4095

    SPI.begin(LCD_SCL, -1, LCD_SDA, LCD_CS);
    tft.init(240, 320); 
    tft.setRotation(1); 
    tft.fillScreen(ST77XX_WHITE); // HOME SCREEN
    delay(1000);

    Wire.begin(SDA, SCL); // Initialize I2C for BMP280
    Wire.setClock(100000);
    sensorOK = bmp.begin(BMP280_ADDRESS);

    if (!sensorOK) {
        tft.setTextColor(ST77XX_RED);
        tft.setTextSize(2);
        tft.setCursor(10, 10);
        tft.println("BMP280 ERROR");
    }

    Home(); // Display the home screen
}

void loop() {
    int x = analogRead(joy_x);
    bool Button = digitalRead(joy_sw);
    Time = millis();
    
    if(page == 0) {
        if (x < 1000) {
            selectBox = 0; // Select Temperature
            Home();
        } else if (x > 3000) {
            selectBox = 1; // Select Pressure
            Home();
        }

        if(lastButton == HIGH && Button == LOW) {
            if(selectBox == 0){
                page = 1;
                TempPage();
            }else {
                page = 2;
                PressurePage();
            }

            oldTime = millis();
        }

    }else{

        if(x < 1000){
            page = 0;
            Home();
        }

        else if(Time - oldTime >= 500) {
            oldTime = Time;
            if(page == 1) {
                TempData();
            }else if(page == 2){
                PressureData();
            }
        }

    }
    lastButton = Button;
    delay(100); 
}


