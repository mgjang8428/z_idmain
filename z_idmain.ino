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

TaskHandle_t Task1;
TaskHandle_t Task2;
TaskHandle_t Task3;

GyroValue gv = { 0, 0, 0, 0, 0, 0 };
GpsValue gp = { false, 0, 0 };
Data data = { DEVICENO, false, gv, gp };


void setup() {
  xTaskCreatePinnedToCore(taskSensor, "Task1", 10000, NULL, 1, &Task1, 0);
  xTaskCreatePinnedToCore(taskLCDWifi, "Task2", 10000, NULL, 1, &Task2, 1);
  xTaskCreatePinnedToCore(taskLoading, "Task3", 10000, NULL, 1, &Task3, 0);
  //pcSerial
  Serial.begin(115200);
  //gpsSerial
  Serial2.begin(9600);
  //gy271, lcd Set
  Wire.begin(21, 22);

  vibeSetup();
  gv = gyroSetup();
  gpsSetup();
  lcdSetup();
  delay(3000);
}

void loop() {
  // task_time = millis();

  // if (task_time - task_sensor >= 100) {
  //   if (data.vibeValue == false) {
  //     data.vibeValue = vibeLoop();
  //   }
  //   Serial.println(data.vibeValue);
  //   data.gyroValue = gyroLoop(gv);
  //   data.gpsValue = gpsLoop();
  // }

  // if (task_time - task_net >= 1000) {
  //   if (WiFi.status() != WL_CONNECTED) {
  //     wifiSetup();
  //   }
  //   if (WiFi.status() == WL_CONNECTED) {
  //     wifiLoop(data);
  //   }
  //   data.vibeValue = false;
  // }

  // if (task_time - task_net >= 2000) {
  //   lcdLoop();
  // }


  // //Test
  // Serial.println(makeDataToJson(data));
  // delay(1000);
}

void taskSensor(void *param) {
  while (1) {
    if (data.vibeValue == false) {
      data.vibeValue = vibeLoop();
    }
    data.gyroValue = gyroLoop(gv);
    data.gpsValue = gpsLoop();
    delay(100);
  }
}

void taskLCDWifi(void *param) {
  while (1) {
    if (WiFi.status() != WL_CONNECTED) {
      wifiSetup();
    }
    if (WiFi.status() == WL_CONNECTED) {
      wifiLoop(data);
    }
    Serial.println(makeDataToJson(data));
    data.vibeValue = false;
    lcdLoop();
    
    delay(5000);
  }
}

void taskLoading(void *param) {
  while (1) {
    lcdLoading();
    delay(1000);
  }
}