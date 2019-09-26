#include "Arduino.h"
#include "magnet.h"
#include "logic.h"

#define MAGNET_PIN 21

Magnet::Magnet(Logic &logic)
: _logic(logic)
{  
}

void Magnet::setup() {
  pinMode(MAGNET_PIN, OUTPUT);
}

void Magnet::handle() {
  digitalWrite(MAGNET_PIN, enabled ? HIGH : LOW);
}

void Magnet::off() {
  _logic.serial.print("disabling magnet...\n");
  enabled = false;
}