#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  
  lcd.print("Poinsys");
  lcd.blink();

  Serial.begin(9600);
}

void loop() {

}
