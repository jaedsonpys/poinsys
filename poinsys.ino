#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

const int ssPin = 10;
const int rstPin = 9;
const int buzzerPin = 2;

const String acceptedIDs[2] = {"397fc9b2", "3cea3764"};

MFRC522 rfid(ssPin, rstPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

String waitRFIDCard();

void setup() {
  lcd.init();
  lcd.backlight();

  SPI.begin();
  rfid.PCD_Init();

  Serial.begin(9600);

  lcd.setCursor(4, 0);
  lcd.print("Poinsys");

  delay(1000);
}

void loop() {
  lcd.clear();
  lcd.print("Aproxime o");
  lcd.setCursor(0, 1);
  lcd.print("cartao");

  String readID = waitRFIDCard();
  bool validID = false;

  for(int i = 0; i < 2; i++) {
    if(readID.equals(acceptedIDs[i])) {
      validID = true;
    }
  }

  if(validID) {
    lcd.clear();
    lcd.setCursor(7, 0);
    lcd.print("OK");

    tone(buzzerPin, 1500);
    delay(90);
    noTone(buzzerPin);
  } else {
    lcd.clear();
    lcd.print("Tente novamente");
  }

  delay(2000);
}

String waitRFIDCard() {
  while(!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    delay(50);
  }

  String uid = "";

  for(byte i = 0; i < rfid.uid.size; i++) {
    uid.concat(String(rfid.uid.uidByte[i], HEX));
  }

  return uid;
}
