#include "Arduino.h"
#include "rfid.h"
#include "logic.h"
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 22

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

byte cards[][4] = { {0xA7, 0x86, 0x8A, 0xF2} };
byte readCard[4];    // Stores scanned ID read from RFID Module

bool found = false;
bool wasFound = false;

Rfid::Rfid(Logic &logic)
: _logic(logic)
{
}

void Rfid::setup() {
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
}

void Rfid::handle() {
  // Look for new cards
  if ( !mfrc522.PICC_IsNewCardPresent() ) {
    found = false;
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial())
    return;

  for(int i=0;i<4;i++){
    readCard[i] = mfrc522.uid.uidByte[i];
  }

  // Authorized
  if(!memcmp(readCard, cards[0],4)){
    found = true;
    wasFound = true;
    Serial.println("authorized");
  }
}
