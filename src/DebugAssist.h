/*
  DebugAssist.h - Library for simplifying debugging functionality.
  Created by Dean Martin, FrostAura Industries, August 14, 2017.
*/
#ifndef DEBUG_ASSIST_H
#define DEBUG_ASSIST_H

#include "Arduino.h"
#include "string.h"

class DebugAssist
{
  public:
    DebugAssist();
    initialize(bool debug);
    printLog(String message);
    printLogLn(String message);
  private:
    bool _debug;
};

#endif

