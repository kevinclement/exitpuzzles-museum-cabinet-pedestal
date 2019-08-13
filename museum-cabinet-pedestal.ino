#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 5
#define RST_PIN 22
#define MAGNET_PIN 21
#define LED_PIN 2
#define RED_PIN 33
#define GREEN_PIN 25
#define BLUE_PIN 32

#define R 1
#define G 2
#define B 3

int freq = 5000;
int resolution = 8;

MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance.
MFRC522::MIFARE_Key key;

byte masterCard[] = { 0x64, 0x26, 0x16, 0x89 };
byte defcard[][4] = { {0xA7, 0x86, 0x8A, 0xF2} };

byte readCard[4];    // Stores scanned ID read from RFID Module

// TODO:  use master key to set valid UID
//    scan master, than turn on light ring
//    scan new tag, then blink light ring
//    store tag info in memory

// TODO: how do we reset it?  
//    controlled from computer?
//    controlled with masterCard?
//    controlled via timeout?

void setup() {
  Serial.begin(115200); // Initialize serial communications with the PC
  SPI.begin();      // Init SPI bus

  pinMode(LED_PIN, OUTPUT);
  pinMode(MAGNET_PIN, OUTPUT);
  
  mfrc522.PCD_Init(); // Init MFRC522 card

  // setup LEDs
  ledcSetup(R, freq, resolution);
  ledcSetup(G, freq, resolution);
  ledcSetup(B, freq, resolution);
  
  ledcAttachPin(RED_PIN,   R);
  ledcAttachPin(GREEN_PIN, G);
  ledcAttachPin(BLUE_PIN,  B);

  Serial.println(F("Scan card"));
}

bool found = false;
bool wasFound = false;
void loop() {

  // DEBUG: turn on built in led when found
  digitalWrite(LED_PIN, found ? HIGH : LOW);
  digitalWrite(MAGNET_PIN, wasFound ? LOW : HIGH);

  if (wasFound) {
    ledcWrite(R, 0);   
    ledcWrite(G, 255); 
    ledcWrite(B, 0);   
  } else {
    ledcWrite(R, 10);
    ledcWrite(G, 0); 
    ledcWrite(B, 0); 
  }
  
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
//    Serial.print(readCard[i],HEX);    
  }
//  Serial.println();

  // Authorized
  if(!memcmp(readCard, defcard[0],4)){
    found = true;
    wasFound = true;
    Serial.println("authorized");
  }

  // Authorized
  if(!memcmp(readCard, masterCard, 4)){
    found = true;
    wasFound = false;
    Serial.println("reset");
  }
}

/**
 * Helper routine to dump a byte array as hex values to Serial.
 */
void dump_byte_array(byte *buffer, byte bufferSize) {
    for (byte i = 0; i < bufferSize; i++) {
        Serial.print(buffer[i] < 0x10 ? " 0" : " ");
        Serial.print(buffer[i], HEX);
    }
}