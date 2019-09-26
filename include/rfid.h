#pragma once

#include "Arduino.h"

class Logic;

class Rfid {
  public:
    Rfid(Logic &logic);
    void setup();
    void handle();

    bool solved = false;
  private:
    Logic &_logic;

};