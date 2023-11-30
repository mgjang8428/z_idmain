void vibeSetup() {
  pinMode(VIBESENSEPIN, INPUT);
}

bool vibeLoop() {
  return digitalRead(VIBESENSEPIN);
}