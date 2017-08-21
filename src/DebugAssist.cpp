/*
  DebugAssist.h - Library for simplifying debugging functionality.
  Created by Dean Martin, FrostAura Industries, August 14, 2017.
*/
#include "Arduino.h"
#include "string.h"
#include "DebugAssist.h"

DebugAssist::DebugAssist()
{ }

DebugAssist::initialize(bool debug)
{
    _debug = debug;
}

DebugAssist::printLog(String message)
{
  if(_debug) Serial.print("DEBUG:: " + message);
}

DebugAssist::printLogLn(String message)
{
  if(_debug) Serial.println("DEBUG:: " + message);
}
