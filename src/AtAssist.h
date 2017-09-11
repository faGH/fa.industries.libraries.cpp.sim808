/*
  AtAssist.h - Library for simplifying AT commands and functionality.
  Created by Dean Martin, FrostAura Industries, August 14, 2017.
*/
#ifndef AT_ASSIST_H
#define AT_ASSIST_H

#include "Arduino.h"
#include "string.h"
#include "SoftwareSerial.h"
#include "DebugAssist.h"

class AtAssist
{
  public:
    AtAssist();
    void initialize(bool debug);
    String sendCommand(SoftwareSerial& connection, String command, int timeout = 1000);
    bool isOk(String commandResponse);
  private:
    bool _debug;
    DebugAssist _debugger;
};

#endif

