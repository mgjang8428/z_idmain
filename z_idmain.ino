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
//#include <HttpClient.h>
#include <ArduinoJson.h>

#include "_idHeader.h"

unsigned long task_time;
unsigned long task_sensor;
unsigned long task_net;

GyroValue gv = { 0, 0, 0 };
GpsValue gp = { false, 0, 0 };
Data data = { DEVICENO, false, gv, gp };


void setup() {
  //pcSerial
  Serial.begin(115200);
  //gpsSerial
  Serial2.begin(9600);
  //gy271, lcd Set
  Wire.begin(21, 22);

  vibeSetup();
  gyroSetup();
  gpsSetup();
  lcdSetup();
  delay(3000);
}

void loop() {
  task_time = millis();

  if (task_time - task_sensor >= 100) {
    data.vibeValue = vibeLoop();
    data.gyroValue = gyroLoop();
    data.gpsValue = gpsLoop();
  }

  if (task_time - task_net >= 1000) {
    if (WiFi.status() != WL_CONNECTED) {
      wifiSetup();
    }
    if (WiFi.status() == WL_CONNECTED ) {
      wifiLoop(data);
    }
  }

  // lcdLoop();

  
  //Test
  Serial.println(makeDataToJson(data));
  delay(1000);
}