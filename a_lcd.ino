LiquidCrystal_I2C lcd(LCDADDR, LCDROW, LCDCOLUMN);

int i = 0;
int loadingValue = 0;
int sendProcessValue = 0;

void lcdSetup() {
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Device Start!!");
  lcd.setCursor(0, 1);
  lcd.print("----------------");
}

void lcdLoop() {
}

void lcdWifiWait() {
  lcd.setCursor(0, 0);
  lcd.print("Try WIFI Connect");
  lcd.setCursor(0, 1);
  lcd.print("               ");
  lcd.setCursor(0, 1);
  lcd.print("Wait!!");
  delay(500);
}

void lcdWifiSuccess() {
  lcd.setCursor(0, 1);
  lcd.print("               ");
  lcd.setCursor(0, 1);
  lcd.print("success!!!");
  delay(5000);
  lcd.clear();
}

void lcdNetDataSend() {
  lcd.setCursor(0, 0);
  lcd.print("Data::");
  lcdSendProcessing();
}

void lcdLoading() {
  lcd.setCursor(15, 1);
  switch (loadingValue) {
    case 0:
      lcd.print("|");
      loadingValue++;
      break;
    case 1:
      lcd.print("/");
      loadingValue++;
      break;
    case 2:
      lcd.print("-");
      loadingValue++;
      break;
    case 3:
      lcd.print("*");
      loadingValue = 0;
      break;
  }
}

void lcdSendProcessing() {
  lcd.setCursor(6, 0);
  switch (sendProcessValue) {
    case 0:
      lcd.print("     ");
      lcd.setCursor(6, 0);
      lcd.print(">");
      sendProcessValue++;
      break;
    case 1:
      lcd.print("->");
      sendProcessValue++;
      break;
    case 2:
      lcd.print("-->");
      sendProcessValue++;
      break;
    case 3:
      lcd.print("--->");
      sendProcessValue++;
      break;
    case 4:
      lcd.print("---->");
      sendProcessValue = 0;
      break;
  }
}

void lcdSendCont(long count, long previousCount) {
  if (count == previousCount) {
    lcd.setCursor(0, 1);
    lcd.print("               ");
    lcd.setCursor(0, 1);
    lcd.print("Server: X");
  } else {
    lcd.setCursor(0, 6);
    lcd.print("         ");
    lcd.setCursor(0, 1);
    lcd.print("Count:");
    lcd.setCursor(6, 1);
    lcd.print(count);
  }
}

void lcdGpsStatus(boolean gpsStatus) {
  lcd.setCursor(11,0);
  lcd.print("GPS:");
  if(gpsStatus) {
    lcd.print("O");
  } else {
    lcd.print("X");
  }
}

void lcd_deviceStart() {
  lcd.clear();
}