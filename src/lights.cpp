#include "Arduino.h"
#include "lights.h"
#include "logic.h"

#define RED_PIN 33
#define GREEN_PIN 25
#define BLUE_PIN 32

#define R 1
#define G 2
#define B 3

#define FREQ 5000
#define RES 8

uint8_t ledColors[][3] = {
  {  10,     0,     0 }, // no-idol (very light red)
  { 255,   100,    50 }, // white
  {   0,     0,   255 }, // blue
  { 255,     0,     0 }, // red
  { 200,     0,   255 }, // purple
  {   0,   255,     0 }, // green
};

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
  ledcWrite(R, ledColors[idol][0]);
  ledcWrite(G, ledColors[idol][1]);
  ledcWrite(B, ledColors[idol][2]);
}

void Lights::on(int i) {
  _logic.serial.print("enabling lights...\n");
  idol = i;
}

void Lights::off() {
  idol = 0;
}
