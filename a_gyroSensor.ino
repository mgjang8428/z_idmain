MechaQMC5883 gyro;

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