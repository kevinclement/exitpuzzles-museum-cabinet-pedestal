#pragma once

#include "Arduino.h"

class Logic;

class Lights {
  public:
    Lights(Logic &logic);
    void setup();
    void handle();

    void on(int i);
    void off();

    int idol = 0;

  private:
    Logic &_logic;
    
};