#include <Arduino.h>
#include <pages.h>
#include<math.h>

/*
//custom color
#define BUTT_COLOR    tft.color565(20, 35, 26)
#define BORDER_COLOR  tft.color565(52, 91, 64)
#define SELECT_COLOR  tft.color565(164, 240, 160)
#define TEXT_COLOR    tft.color565(183, 221, 176)
#define TEXT_COLOR2   tft.color565(88, 118, 90)
*/

float Altitude;

void DrawPage(String name) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_YELLOW);
    tft.setTextSize(3);
    tft.setCursor(60, 25);
    tft.println(name);
}

void Home() {
    
    tft.fillScreen(ST77XX_BLACK);

    tft.fillRect(0, 40, 300, 3, ST77XX_YELLOW); // vertical line



    tft.fillRect(160, 40, 3, 90, ST77XX_YELLOW); // horizontal line

    tft.fillRect(0, 130, 320, 3, ST77XX_YELLOW); // 
    tft.drawFastHLine(0, 130, 320, ST77XX_YELLOW); // vertical line

    tft.setTextColor(ST77XX_YELLOW);
    tft.setTextSize(3);
    tft.setCursor(20, 10);
    tft.println("Weather Station");

    tft.setTextColor(ST77XX_YELLOW);
    tft.setTextSize(2);
    tft.setCursor(20, 210);
    tft.println("hPa = mbar");


    
    //Temperature Button
    if(selectBox == 0) {
        tft.fillRect(0, 40, 160, 40, ST77XX_YELLOW); // x, y, width, height
        tft.setTextColor(ST77XX_BLACK);
        tft.setTextSize(2);
        tft.setCursor(15, 50);
        tft.println("Temperature");
    } else {
        tft.setTextColor(ST77XX_YELLOW);
        tft.setTextSize(2);
        tft.setCursor(15, 50);
        tft.println("Temperature");
    }

    //Pressure Button
    if(selectBox == 1) {
        tft.fillRect(160, 40, 160, 40, ST77XX_YELLOW);
        tft.setTextColor(ST77XX_BLACK);
        tft.setTextSize(2);
        tft.setCursor(190, 50);
        tft.println("Pressure");
        
    } else {
        tft.setTextColor(ST77XX_YELLOW);
        tft.setTextSize(2);
        tft.setCursor(190, 50);
        tft.println("Pressure");
    }

     //Altitude Button
    if(selectBox == 2) {
        tft.fillRect(0, 90, 160, 40, ST77XX_YELLOW);
        tft.setTextColor(ST77XX_BLACK);
        tft.setTextSize(2);
        tft.setCursor(15, 100);
        tft.println("Altitude");
    } else {
        tft.setTextColor(ST77XX_YELLOW);
        tft.setTextSize(2);
        tft.setCursor(15, 100);
        tft.println("Altitude");
    }

    // Input box
    if(selectBox == 3) {
        tft.fillRect(160, 90, 160, 40, ST77XX_YELLOW);
        tft.setTextColor(ST77XX_BLACK);
        tft.setTextSize(2);
        tft.setCursor(190, 100);
        tft.println("Sea-Level");
        
    } else {
        tft.setTextColor(ST77XX_YELLOW);
        tft.setTextSize(2);
        tft.setCursor(190, 100);
        tft.println("Sea-Level");
    }
}

void SeaLevel() {

    tft.setTextColor(ST77XX_YELLOW);
    tft.setTextSize(2);
    tft.setCursor(20, 210);
    tft.println("Test");
}


void TempData(){
    tft.fillRect(90,100,200,40, ST77XX_BLACK);

    if(sensorOK){
        double temp = bmp.readTemperature();
        tft.setCursor(90, 100);
        tft.print(temp, 1);
        tft.println(" C");
    }else {
        tft.setTextSize(2);
        tft.setTextColor(ST77XX_RED);
        tft.println("BMP ERROR");
    }
}

void TempPage() {
    DrawPage("Temperature");
}

void PressurePage() {
    DrawPage("Pressure");
}

void AltitudePage() {
    DrawPage("Altitude");
}

void SeaLevelPage(){
    DrawPage("SeaLevel");
}


void PressureData() {

    double pressure = bmp.readPressure() / 100; // Pa, Pa/100 = hPa (atmosphere pressure)

    tft.fillRect(60,60,200,40, ST77XX_BLACK); // clear screen, combining texts

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


void AltitudeData() {
    tft.fillRect(60,60,200,40, ST77XX_BLACK); // clear previous page
    Altitude = 44330 * (1 - pow(bmp.readPressure() / 101325.0, 0.1903)); // in m

    tft.setTextSize(3);
    tft.setTextColor(ST77XX_GREEN);
    tft.setCursor(60, 60);
    tft.print(Altitude, 1); // decimal point
    tft.println(" m");
}


