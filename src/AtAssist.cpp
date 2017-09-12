/*
  AtAssist.h - Library for simplifying AT commands and functionality.
  Created by Dean Martin, FrostAura Industries, August 14, 2017.
*/
#include "string.h"
#include "SoftwareSerial.h"
#include "AtAssist.h"
#include "DebugAssist.h"

AtAssist::AtAssist()
{ }

void AtAssist::initialize(bool debug)
{
    _debug = debug;
    _debugger.initialize(debug);
}

String AtAssist::sendCommand(SoftwareSerial& connection, String command, int timeout /*= 1000*/)
{
    String response = "";
     
    _debugger.printLogLn("SERIAL REQUEST:: '" + command + "'");
    connection.println(command);

    long int time = millis();
    while((time+timeout) > millis())
    {
      while(connection.available())
      {
        char c = connection.read();
        
        response+=c;
      }  
    }  

    _debugger.printLogLn("SERIAL RESPONSE:: '" + response + "'");
      
    return response;
}

bool AtAssist::isOk(String commandResponse)
{
    return commandResponse.indexOf("OK") > -1;
}
