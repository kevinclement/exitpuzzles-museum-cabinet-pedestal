#pragma once

#include "SerialManager.h"
#include "rfid.h"
#include "lights.h"
#include "magnet.h"
#include "sound.h"

class Logic {
public:
  Logic();
  SerialManager serial;
  Rfid rfid;
  Lights lights;
  Magnet magnet;
  Sound sound;

  void setup();
  void handle();
  void solved();
  void status();

private:
  
};

