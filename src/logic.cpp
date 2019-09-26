#include "Arduino.h"
#include "logic.h"
#include "consts.h"

unsigned long solved_at = 0;
bool stopped_all = false;

Logic::Logic() 
  : serial(),
    actuator(*this),
    lights(*this),
    lightsensors(*this),
    sound(*this)
{
}

void Logic::setup() {
  serial.setup("ExitMuseumMummy");

  actuator.setup();
  lights.setup();
  lightsensors.setup();
  sound.setup();

  // trigger a close, if its already closed then noop
  // if this is a reset, then close here will do the actual close
  actuator.close();
}

void Logic::handle() {
  serial.handle();
  lightsensors.handle();
  lights.handle();
  actuator.handle();

  if (lightsensors.lightDetected && solved_at == 0) {
    solved();
  }

  // don't start the flashing until a few seconds to sync with audio
  if (!stopped_all && !lights.lights_on && solved_at > 0 && millis() - solved_at > 2800) {
    lights.on();
  }

  if (!stopped_all && solved_at != 0 && actuator.opened) {
    serial.print("All done with lights and music!\n");
    sound.stop();
    lights.off();
    stopped_all = true;
  }
}

void Logic::solved() {
  serial.print("Solved!\n");

  sound.play();
  actuator.open();

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
