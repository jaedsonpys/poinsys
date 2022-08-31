#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

const int ssPin = 10;
const int rstPin = 9;

MFRC522 rfid(ssPin, rstPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  lcd.init();
  lcd.backlight();
  
  lcd.print("Poinsys");
  lcd.blink();

  SPI.begin();
  rfid.PCD_Init();

  Serial.begin(9600);
}

void loop() {

}
