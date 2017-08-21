/*
  DebugAssist.h - Library for simplifying debugging functionality.
  Created by Dean Martin, FrostAura Industries, August 14, 2017.
*/
#include "string.h"
#include "DebugAssist.h"

DebugAssist::DebugAssist()
{ }

void DebugAssist::initialize(bool debug)
{
    _debug = debug;
}

void DebugAssist::printLog(String message)
{
  if(_debug) Serial.print("DEBUG:: " + message);
}

void DebugAssist::printLogLn(String message)
{
  if(_debug) Serial.println("DEBUG:: " + message);
}
