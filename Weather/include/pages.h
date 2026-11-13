#ifndef PAGES_H
#define PAGES_H

#include <Adafruit_GFX.h>    
#include <Adafruit_ST7789.h> 
#include <Adafruit_BMP280.h> 


// gotta let know these variables and objects
extern int selectBox;
extern Adafruit_ST7789 tft;
extern bool sensorOK;
extern Adafruit_BMP280 bmp; 

void Home();
void TempData();
void TempPage();
void PressureData();
void PressurePage();
#endif