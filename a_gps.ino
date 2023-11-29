TinyGPSPlus gps;

void gpsSetup() {}

GpsValue gpsLoop() {
  GpsValue gpsValue{ false, 0, 0 };
  //updateSerial();
  while (Serial2.available() > 0) {  //while(Serial2.available() > 0)
    if (gps.encode(Serial2.read())) {
      // displayInfo();
      if (gps.location.isValid()) {
        gpsValue.stat = true;
        gpsValue.lat = gps.location.lat();
        gpsValue.lng = gps.location.lng();
      } else {
        gpsValue.stat = false;
        gpsValue.lat = 0;
        gpsValue.lng = 0;
      }
    }
  }
  if (millis() > 5000 && gps.charsProcessed() < 10) {
    // Serial.println(F("No GPS detected: check wiring."));
    //while (true) {}
  }
  // if (Serial2.available()) {
  //   Serial.println("Serial2 OK!!");
  //   if (gps.encode(Serial2.read())) {
  //     Serial.println("gps.encode OK!!");
  //     if (gps.location.isValid()) {
  //       Serial.println("gps.isValid OK!!");
  //       gpsValue.stat = true;
  //       gpsValue.lat = gps.location.lat();
  //       gpsValue.lng = gps.location.lng();
  //     } else {
  //       Serial.println("gps.InValid OK!!");
  //       gpsValue.stat = false;
  //       gpsValue.lat = 0;
  //       gpsValue.lng = 0;
  //     }
  //   }
  // }
  return gpsValue;
}

//gps
void displayInfo() {
  Serial.print(F("Location: "));
  if (gps.location.isValid()) {
    Serial.print("Lat: ");
    Serial.print(gps.location.lat(), 6);
    Serial.print(F(","));
    Serial.print("Lng: ");
    Serial.print(gps.location.lng(), 6);
    Serial.println();
  } else {
    Serial.println(F("INVALID"));
  }
}
//gps
void updateSerial() {
  delay(500);
  while (Serial.available()) {
    Serial2.write(Serial.read());  //Forward what Serial received to Software Serial Port
  }
  while (Serial2.available()) {
    Serial.write(Serial2.read());  //Forward what Software Serial received to Serial Port
  }
}