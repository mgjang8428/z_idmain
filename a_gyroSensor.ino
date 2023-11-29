MechaQMC5883 gyro;

void gyroSetup() {
  gyro.init();
}

void gyroLoop() {
  int x, y, z;
  gyro.read(&x, &y, &z);
  Serial.print("x: ");
  Serial.print(x);
  Serial.print(" y: ");
  Serial.print(y);
  Serial.print(" z: ");
  Serial.print(z);
  Serial.println();
}