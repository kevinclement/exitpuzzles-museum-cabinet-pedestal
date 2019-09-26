#include "Arduino.h"
#include "lights.h"

#define RED_PIN 33
#define GREEN_PIN 25
#define BLUE_PIN 32

#define R 1
#define G 2
#define B 3

#define FREQ 5000
#define RES 8

Lights::Lights(Logic &logic)
: _logic(logic)
{  
}

void Lights::setup() {
  ledcSetup(R, FREQ, RES);
  ledcSetup(G, FREQ, RES);
  ledcSetup(B, FREQ, RES);

  ledcAttachPin(RED_PIN,   R);
  ledcAttachPin(GREEN_PIN, G);
  ledcAttachPin(BLUE_PIN,  B);
}

void Lights::handle() {
  if (_enabled) {
    ledcWrite(R, 0);
    ledcWrite(G, 255);
    ledcWrite(B, 0);
  } else {
    ledcWrite(R, 10);
    ledcWrite(G, 0);
    ledcWrite(B, 0);
  }
}

void Lights::on() {
  _enabled = true;
}

void Lights::off() {
  _enabled = false;
}
