#include "Arduino.h"
#include "lights.h"

#define BETWEEN 2579
#define DURATION 43 
#define TIMES 7
#define FREQ 5000
#define RES 8
#define CHANNEL 0

unsigned long lastTime = 0;
int waitTime = 1500;

Lights::Lights(Logic &logic)
: _logic(logic)
{  
}

void flash() {
  for (int i=0; i< random(TIMES); i++)
  {
    ledcWrite(CHANNEL, 255);
    delay(62);
    ledcWrite(CHANNEL, 0);
    delay(10);
  }
}

void Lights::on() {
  lights_on = true;
  lastTime = 0;
}

void Lights::allOn() {
  ledcWrite(CHANNEL, 255);
}

void Lights::off() {
  ledcWrite(CHANNEL, 0);
  lights_on = false;
}

void Lights::setup() {
  ledcSetup(CHANNEL, FREQ, RES);
  ledcAttachPin(27, CHANNEL);
}

void Lights::handle() {
  if (lights_on) {
    if (millis() - lastTime > waitTime)  // time for a new flash
    {
      // adjust timing params
      flash();
      lastTime = millis();
    }
  }
}
