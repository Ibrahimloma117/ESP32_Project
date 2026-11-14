#include <Arduino.h>
#include <pages.h>

//custom color
#define BUTT_COLOR    tft.color565(20, 35, 26)
#define BORDER_COLOR  tft.color565(52, 91, 64)
#define SELECT_COLOR  tft.color565(164, 240, 160)
#define TEXT_COLOR    tft.color565(183, 221, 176)
#define TEXT_COLOR2   tft.color565(88, 118, 90)


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

void TempData(){
    tft.fillRect(60,60,200,40, ST77XX_BLACK);

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

void DrawPage(String name) {
    tft.fillScreen(ST77XX_BLACK);
    tft.setTextColor(ST77XX_GREEN);
    tft.setTextSize(3);
    tft.setCursor(60, 25);
    tft.println(name);
}

void TempPage() {
    DrawPage("Temperature");
}

void PressurePage() {
    DrawPage("Pressure");
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
