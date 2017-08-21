#include "AtAssist.h"
#include "SoftwareSerial.h"
#include "string.h"

#define DEBUG true

AtAssist at;
SoftwareSerial connection(11, 12);

void setup() {
  at.initialize(DEBUG);
}

void loop() {
  bool isCommandSuccessfullySent = isCommandSent("SOME AT COMMAND");
}

bool isCommandSent(String command){
  String response = at.sendCommand(connection, command);

  return at.isOk(response);
}
