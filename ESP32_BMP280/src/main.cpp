
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_BMP280.h>

#define SDA_PIN 8
#define SCL_PIN 9

Adafruit_BMP280 bmp;

void setup() {
    Serial.begin(115200);
    delay(2000);

    Wire.begin(SDA_PIN, SCL_PIN);

    Serial.println("Starting BMP280...");

    if (!bmp.begin(0x76)) {
        if (!bmp.begin(0x77)) {
            Serial.println("BMP280 not found!");
            while (1) {
                delay(1000);
            }
        }
    }

    Serial.println("BMP280 connected!");
}

void loop() {
    double temperature = bmp.readTemperature();
    double pressure = bmp.readPressure() / 100.0f;
    double altitude = bmp.readAltitude(1013.25f);

    Serial.printf("Temperature: %.2f C\n", temperature);
    Serial.printf("Pressure: %.2f hPa\n", pressure);
    Serial.printf("Altitude: %.2f m\n", altitude);

    Serial.println("---------------------");

    delay(1000);
}
