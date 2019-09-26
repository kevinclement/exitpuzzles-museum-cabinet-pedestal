#pragma once

#include "Arduino.h"

class Logic;

class Rfid {
  public:
    Rfid(Logic &logic);
    void setup();
    void handle();

    bool solved = false;
    int idol = 0;
  private:
    Logic &_logic;

};