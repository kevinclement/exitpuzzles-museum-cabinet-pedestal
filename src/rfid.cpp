#include "Arduino.h"
#include "rfid.h"
#include "logic.h"
#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 22

// functions
int compareTags();

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

#define NUM_IDOLS 5
byte idols[][4] = {
  { 0xA7, 0x86, 0x8A, 0xF2 },
  { 0xF7, 0x81, 0x8A, 0xF2 }, 
  { 0x07, 0x83, 0x8A, 0xF2 },
  { 0xF7, 0x6F, 0x8C, 0xF2 },
  { 0x97, 0x6F, 0x8C, 0xF2 },
};

byte readCard[4];    // Stores scanned ID read from RFID Module
bool rfid_tag_present_prev = false;
bool rfid_tag_present = false;
int _rfid_error_counter = 0;
bool _tag_found = false;

Rfid::Rfid(Logic &logic)
: _logic(logic)
{
}

void Rfid::setup() {
  SPI.begin();        // Init SPI bus
  mfrc522.PCD_Init(); // Init MFRC522 card
}

void Rfid::handle() {
  rfid_tag_present_prev = rfid_tag_present;

  _rfid_error_counter += 1;
  if(_rfid_error_counter > 2){
    _tag_found = false;
  }

  // Detect Tag without looking for collisions
  byte bufferATQA[2];
  byte bufferSize = sizeof(bufferATQA);

  // Reset baud rates
  mfrc522.PCD_WriteRegister(mfrc522.TxModeReg, 0x00);
  mfrc522.PCD_WriteRegister(mfrc522.RxModeReg, 0x00);

  // Reset ModWidthReg
  mfrc522.PCD_WriteRegister(mfrc522.ModWidthReg, 0x26);

  MFRC522::StatusCode result = mfrc522.PICC_RequestA(bufferATQA, &bufferSize);

  if(result == mfrc522.STATUS_OK){
    if ( ! mfrc522.PICC_ReadCardSerial()) { //Since a PICC placed get Serial and continue   
      return;
    }
    _rfid_error_counter = 0;
    _tag_found = true;

    for ( uint8_t i = 0; i < 4; i++) {
       readCard[i] = mfrc522.uid.uidByte[i];
    }
  }

  rfid_tag_present = _tag_found;
  
  // tag found
  if (rfid_tag_present && !rfid_tag_present_prev){
    _logic.serial.print("tag found.\n");
    idol = compareTags();
  }

  // tag removed
  if (!rfid_tag_present && rfid_tag_present_prev){
    _logic.serial.print("tag removed.\n");
    idol = 0;
  }
}

int compareTags() {
  for ( uint8_t j = 0; j < NUM_IDOLS; j++) {
    for ( uint8_t k = 0; k < 4; k++ ) {
      if ( readCard[k] != idols[j][k] ) {
        return j + 1;
      }
    }
  }

  return 0;
}