#pragma once

#include "Arduino.h"

class Logic;

class Lights {
  public:
    Lights(Logic &logic);
    void setup();
    void handle();

    void on();
    void off();

    bool enabled = false;

  private:
    Logic &_logic;
    
};