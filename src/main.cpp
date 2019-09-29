#include <Arduino.h>
#include "logic.h"
#include "consts.h"
#include "version.h"

// Globals
Logic logic;

void reboot(int) {
  ESP.restart();
}

void status(int) {
  logic.status();
}

void solve(int) {
  logic.serial.print("forcing a solve...%s", CRLF);
  logic.solved();
}

void two(int) {
  logic.serial.print("faking idol 2...%s", CRLF);
  logic.rfid.idol = 2;
}

void setup() {
  logic.setup();
  logic.serial.print("Museum Cabinet Pedestal by kevinc...\n");
  Serial.println(getFullVersion("museum-cabinet-pedestal"));

  logic.serial.registerCommand(SerialCommand("status", 's', &status, "status", "gets the status of device"));
  logic.serial.registerCommand(SerialCommand("solve",  'v', &solve,  "solve",  "force a solve and open the cabinet"));
  logic.serial.registerCommand(SerialCommand("reboot", 'r', &reboot, "reboot", "software reboot the device"));
  
  logic.serial.registerCommand(SerialCommand("two", '2', &two, "two", "fake idol 2 showing up"));

  logic.serial.printHelp();
  logic.status();
}

void loop() {
  logic.handle();
}
