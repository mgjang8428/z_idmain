/**
* 핀 번호 기록
* 진동감지: D4
* 가속도 : SCL > D22, SDA > D21
* GPS : RX > TX2, TX > RX2
* LCD : SCL > D22, SDA > D21
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MechaQMC5883.h>
#include <TinyGPSPlus.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <HttpClient.h>
//#include <ArduinoJson.h>

#include "_idHeader.h"

void setup() {
  //pcSerial
  Serial.begin(115200);
  //gps
  Serial2.begin(9600);
  //gy271, lcd
  Wire.begin(21, 22);

  wifiSetup();
  wifiLoop();

  // vibeSetup();
  // lcdSetup();
  // gyroSetup();
}

void loop() {
  // vibeLoop();
  // gyroLoop();
  // gpsLoop();
  // lcdLoop();

  // wifiLoop();

  delay(300);
}