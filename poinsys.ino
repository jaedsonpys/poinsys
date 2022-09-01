#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#include <DS1302.h>

const int ssPin = 10;
const int rstPin = 9;
const int buzzerPin = 2;

const String acceptedIDs[2] = {"397fc9b2", "3cea3764"};

MFRC522 rfid(ssPin, rstPin);
DS1302 rtc(5, 4, 3);
LiquidCrystal_I2C lcd(0x27, 16, 2);

String readRFIDCard();

void setup() {
  lcd.init();
  lcd.backlight();

  SPI.begin();
  rfid.PCD_Init();

  Serial.begin(9600);

  rtc.halt(false);
  rtc.writeProtect(false);

  rtc.setDate(1, 1, 2022);
  rtc.setTime(0, 0, 0);

  lcd.setCursor(4, 0);
  lcd.print("Poinsys");

  delay(1000);
}

void loop() {
  String timeStr = rtc.getTimeStr();
  int timeLen = timeStr.length();
  int cursorPos = (16 - timeLen) / 2;

  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("Bem vindo!");
  lcd.setCursor(cursorPos, 1);
  lcd.print(timeStr);

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
