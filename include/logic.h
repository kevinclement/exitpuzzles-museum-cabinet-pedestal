#pragma once

#include "SerialManager.h"
#include "rfid.h"
#include "lights.h"
#include "magnet.h"
#include "WifiUpdate.h"

class Logic {
public:
  Logic();
  SerialManager serial;
  Rfid rfid;
  Lights lights;
  Magnet magnet;
  WifiUpdate wifi;

  void setup();
  void handle();
  void solved();
  void status();

private:
  
};

