//gyro object
MechaQMC5883 gyro;
//gps object
TinyGPSPlus gps;

void vibeSetup() {
  pinMode(VIBESENSEPIN, INPUT);
}

bool vibeLoop() {
  return digitalRead(VIBESENSEPIN);
}

void gyroSetup() {
  gyro.init();
}

GyroValue gyroLoop() {
  int x, y, z;
  GyroValue gyroValue = { 0, 0, 0 };
  gyro.read(&x, &y, &z);
  gyroValue.x = x;
  gyroValue.y = y;
  gyroValue.z = z;
  return gyroValue;
}

void gpsSetup() {}

GpsValue gpsLoop() {
  GpsValue gpsValue{ false, 0, 0 };
  while (Serial2.available() > 0) {
    if (gps.encode(Serial2.read())) {
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