#include "Arduino.h"
#include "rfid.h"
#include "logic.h"
#include <SPI.h>

Rfid::Rfid(Logic &logic)
: _logic(logic)
{
}

void Rfid::setup() {
}

void Rfid::handle() {
}
