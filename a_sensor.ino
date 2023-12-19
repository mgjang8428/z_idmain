//gyro object
// MechaQMC5883 gyro;
// MPU6050 mpu(Wire);
//gps object
TinyGPSPlus gps;

void vibeSetup() {
  pinMode(VIBESENSEPIN, INPUT);
}

bool vibeLoop() {
  return digitalRead(VIBESENSEPIN);
}

GyroValue gyroSetup() {
  int x, y, z;
  GyroValue gv = { 0, 0, 0, 0, 0, 0 };

  mpu.begin();
  mpu.calcGyroOffsets();
  mpu.update();
  gv.initX = mpu.getAngleX();
  gv.initY = mpu.getAngleY();
  gv.initZ = mpu.getAngleZ();

  return gv;
}

GyroValue gyroLoop(GyroValue gv) {
  int x, y, z;
  GyroValue gyroValue = { 0, 0, 0, gv.initX, gv.initY, gv.initZ};

  gyroValue.x = mpu.getAngleX() - gv.initX;
  gyroValue.y = mpu.getAngleY() - gv.initY;
  gyroValue.z = mpu.getAngleZ() - gv.initZ;


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
    Serial2.write(Serial.read());
  }
  while (Serial2.available()) {
    Serial.write(Serial2.read());
  }
}