#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>

const int ssPin = 10;
const int rstPin = 9;
const int buzzerPin = 2;

const String acceptedIDs[2] = {"397fc9b2", "3cea3764"};

MFRC522 rfid(ssPin, rstPin);
LiquidCrystal_I2C lcd(0x27, 16, 2);

String readRFIDCard();

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
  String timeStr = "";
  String dateStr = "";

  lcd.clear();
  lcd.setCursor(4, 0);
  lcd.print("Aproxime");
  lcd.setCursor(3, 1);
  lcd.print(dateStr);

  String readID = readRFIDCard();
  
  if(readID != "") {
    bool validID = false;

    for(int i = 0; i < 2; i++) {
      if(readID.equals(acceptedIDs[i])) {
        validID = true;
      }
    }

    if(validID) {
      lcd.clear();
      lcd.setCursor(3, 0);
      lcd.print("Bem vindo!");

      lcd.setCursor(4, 1);
      lcd.print(timeStr);

      tone(buzzerPin, 1500);
      delay(90);
      noTone(buzzerPin);
    } else {
      lcd.clear();
      lcd.setCursor(6, 0);
      lcd.print("Nao");
      lcd.setCursor(2, 1);
      lcd.print("reconhecido");
    }

    delay(2000);
  } else {
    delay(500);
  }
}

String readRFIDCard() {
  String uid = "";

  if(rfid.PICC_IsNewCardPresent() && rfid.PICC_ReadCardSerial()) {
    for(byte i = 0; i < rfid.uid.size; i++) {
      uid.concat(String(rfid.uid.uidByte[i], HEX));
    }
  }

  return uid;
}
