void vibeSetup() {
  pinMode(VIBESENSEPIN, INPUT);
}

void vibeLoop() {
  bool vibe = digitalRead(VIBESENSEPIN);
  if (vibe) {
    Serial.println("vibe : true");
  }
}