/**
* 핀 번호 기록
* 진동감지: D4
* 가속도 : SCL > D22, SDA > D21
* GPS : RX > TX2, TX > RX2
* LCD : SCL > D22, SDA > D21
*/

/**
* 설치 라이브러리 목록
* ide: ArduinoJson, LiquidCrystal I2C
* zip: MechaQMC5883(gy271), TinyGPSPlus
*/

#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MechaQMC5883.h>
#include <TinyGPSPlus.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <HttpClient.h>
#include <ArduinoJson.h>

#include "_idHeader.h"

GyroValue gv = { 0, 0, 0 };
GpsValue gp = { false, 0, 0 };
Data data = { DEVICENO, false, gv, gp };

//test
int loopLife = 1;


void setup() {

  //pcSerial
  Serial.begin(115200);
  //gps
  Serial2.begin(9600);
  //gy271, lcd
  Wire.begin(21, 22);

  wifiSetup();
  vibeSetup();
  gyroSetup();
  gpsSetup();
  // lcdSetup();
  delay(3000);
}

void loop() {
  if (loopLife) {
    data.vibeValue = vibeLoop();
    data.gyroValue = gyroLoop();
    data.gpsValue = gpsLoop();
    // lcdLoop();

    wifiLoop(data);
    //Test
    Serial.println(makeDataToJson(data));
    delay(1000);
  }
  // loopLife = 0;
}