void vibeSetup() {
  pinMode(VIBESENSEPIN, INPUT);
}

bool vibeLoop() {
  // bool vibe = digitalRead(VIBESENSEPIN);
  // if (vibe) {
  //   Serial.println("vibe : true");
  // }
  return digitalRead(VIBESENSEPIN);
}