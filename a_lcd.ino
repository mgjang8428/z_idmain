LiquidCrystal_I2C lcd(LCDADDR, LCDROW, LCDCOLUMN);

int i = 0;

void lcdSetup() {
  lcd.init();
  lcd.backlight();
}

void lcdLoop() {
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hello, World");
  lcd.setCursor(0,1);
  lcd.print(i);
  i++;
}

void lcd_deviceStart() {
  lcd.clear();
}