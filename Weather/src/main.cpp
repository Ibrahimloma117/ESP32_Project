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

//custom color
//#define BG_COLOR      tft.color565(20, 13, 19)
#define BUTT_COLOR    tft.color565(20, 35, 26)
#define BORDER_COLOR  tft.color565(52, 91, 64)
#define SELECT_COLOR  tft.color565(164, 240, 160)
#define TEXT_COLOR    tft.color565(183, 221, 176)
#define TEXT_COLOR2   tft.color565(88, 118, 90)



bool sensorOK = false;
bool lastButton = HIGH;
int page = 0; // home = 0, Temp = 1, Press = 2
Adafruit_ST7789 tft = Adafruit_ST7789(LCD_CS, LCD_DC, LCD_RST);
Adafruit_BMP280 bmp; // I2C
uint32_t Time, oldTime = 0;

int selectBox = 0;

void Home() {
    
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(2);
    tft.setCursor(60, 25);
    tft.println("Weather Station");

    //Temperature Button
    if(selectBox == 0) {
        tft.fillRect(60, 80, 200, 40, SELECT_COLOR); // x, y, width, height
    } else {
        tft.drawRect(60, 80, 200, 40, BORDER_COLOR);
    }

    //Pressure Button
    if(selectBox == 1) {
        tft.fillRect(60, 140, 200, 40, SELECT_COLOR);
    } else {
        tft.drawRect(60, 140, 200, 40, BORDER_COLOR);
    }

    //box labels
    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(2);
    tft.setCursor(70, 90);
    tft.println("Temperature");
    tft.setCursor(70, 150);
    tft.println("Pressure");
}

void Temperature(){
   // tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(3);
    tft.setCursor(60, 25);
    tft.println("Temperature");

    if(sensorOK){
        double temp = bmp.readTemperature();
        tft.setCursor(60, 60);
        tft.print(temp, 1);
        tft.println(" C");
    }else {
        tft.setTextSize(2);
        tft.setTextColor(ST77XX_RED);
        tft.println("BMP ERROR");
    }
}

void Pressure() {
    //tft.fillScreen(ST77XX_BLACK); // screen flicker test
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(3);
    tft.setCursor(60, 25);
    tft.println("Pressure");

    double pressure = bmp.readPressure() / 100; // Pa, Pa/100 = hPa (atmosphere pressure)

    tft.setTextSize(3);
    tft.setTextColor(ST77XX_GREEN);
    tft.setCursor(60, 60);
    tft.print(pressure, 1); // decimal point

    
    tft.println(" hPa");

    tft.setTextSize(2);
    tft.setCursor(60, 160);
    if(pressure > 1020) {
        tft.setTextColor(ST77XX_GREEN);
        tft.setCursor(60, 160);
        tft.println("High Pressure");
    }else if(pressure < 1000) 
        {
        tft.setTextColor(ST77XX_RED);
        tft.setCursor(60, 100);
        tft.println("Low Pressure");
        }else{
            tft.setTextColor(ST77XX_YELLOW);
            tft.setCursor(60, 100);
            tft.println("Normal Pressure");
        }


}

void setup() {
    Serial.begin(115200);
    Serial.println("Weather Station Starting...");
    pinMode(joy_sw, INPUT_PULLUP);
    analogReadResolution(12); // 12bits, 4095

    SPI.begin(LCD_SCL, -1, LCD_SDA, LCD_CS);
    tft.init(240, 320); 
    tft.setRotation(1); 
    tft.fillScreen(ST77XX_BLACK); // HOME SCREEN
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
                Temperature();
            }else {
                page = 2;
                Pressure();
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
                Temperature();
            }else if(page == 2){
                Pressure();
            }
        }

    }

        
            

    lastButton = Button;
    delay(100); 
}


