#include "Arduino.h"
#include "logic.h"
#include "consts.h"

unsigned long solved_at = 0;
uint8_t _idol = 0;

Logic::Logic() 
  : serial(),
    rfid(*this),
    lights(*this),
    magnet(*this)
{
}

void Logic::setup() {
  serial.setup("ExitMuseumCabinet");

  rfid.setup();
  lights.setup();
  magnet.setup();
}

void Logic::handle() {
  serial.handle();
  magnet.handle();
  lights.handle();
  rfid.handle();

  if (rfid.idol != _idol) {
    _idol = rfid.idol;

    if (_idol == 1 && solved_at == 0) {
      serial.print("cabinet idol found.\n");
      solved();
    }

    status();
  }
}

void Logic::solved() {
  serial.print("Solved!\n");
  solved_at = millis();
  
  lights.on();
  magnet.off();

  status();
}

void Logic::status() {
  char cMsg[254];
  sprintf(cMsg, 
    "status="
      "version:%s,"
      "gitDate:%s,"
      "buildDate:%s,"
      "solved:%s,"
      "lights:%s,"
      "magnet:%s,"
      "idol:%d"
      "%s"
    , GIT_HASH,
      GIT_DATE,
      DATE_NOW,
      solved_at > 0 ? "true" : "false",
      lights.enabled ? "true" : "false",
      magnet.enabled ? "true" : "false",
      rfid.idol,
      CRLF);

  serial.print(cMsg);
}
