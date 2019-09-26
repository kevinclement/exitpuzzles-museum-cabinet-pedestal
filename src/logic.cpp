#include "Arduino.h"
#include "logic.h"
#include "consts.h"

unsigned long solved_at = 0;

Logic::Logic() 
  : serial(),
    rfid(*this),
    lights(*this),
    magnet(*this),
    sound(*this)
{
}

void Logic::setup() {
  serial.setup("ExitMuseumMummy");

  rfid.setup();
  lights.setup();
  magnet.setup();
  sound.setup();
}

void Logic::handle() {
  serial.handle();
  magnet.handle();
  lights.handle();
  rfid.handle();
}

void Logic::solved() {
  serial.print("Solved!\n");

  solved_at = millis();
  status();
}

void Logic::status() {
  char cMsg[254];
  sprintf(cMsg, 
    "status="
      "version:%s,"
      "gitDate:%s,"
      "buildDate:%s,"
      "solved:%s"
      "%s"
    , GIT_HASH,
      GIT_DATE,
      DATE_NOW,
      solved_at > 0 ? "true" : "false",
      CRLF);

  serial.print(cMsg);
}
