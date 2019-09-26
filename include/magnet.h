#pragma once

#include "Arduino.h"

class Logic;

class Magnet {
  public:
    Magnet(Logic &logic);
    void setup();
    void handle();

    void off();
    
    bool enabled = true;
  private:
    Logic &_logic;
    
};