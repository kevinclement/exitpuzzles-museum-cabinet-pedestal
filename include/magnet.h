#pragma once

#include "Arduino.h"

class Logic;

class Magnet {
  public:
    Magnet(Logic &logic);
    void setup();
    void handle();

    void on();
    void off();

  private:
    Logic &_logic;
    bool _enabled = true;
};