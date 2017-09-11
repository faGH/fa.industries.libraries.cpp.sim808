/*
  Sim808.h - Library for simplifying the usage of a Sim808 module.
  Created by Dean Martin, FrostAura Industries, August 14, 2017.

  Purchase module from https://www.aliexpress.com/item/SIM808-development-board-instead-of-908-GSM-GPRS-GPS-Bluetooth-SMS-module-to-send-data-procedures/32748301433.html?spm=a2g0s.9042311.0.0.sWTPVd
*/
#include "SoftwareSerial.h"
#include "TinyGPS++.h"
#include "Sim808.h"
#include "DebugAssist.h"
#include "AtAssist.h"

Sim808::Sim808(int rxPin, int txPin) : _connection(rxPin, txPin)
{ 
  _gpsEnabled = false;
  _gsmEnabled = false;
}

void Sim808::initialize(int baudRate, bool debug)
{
  _debug = debug;
  _debugger.initialize(debug);
  _at.initialize(debug);
  _debugger.printLogLn("Initializing Sim808 at " + String(baudRate));
  _connection.begin(baudRate);
}

bool Sim808::enableGsm(String apn, String username /*= ""*/, String password /*= ""*/)
{
  _debugger.printLogLn("Enabling GSM");

  _debugger.printLogLn("Checking signal quality");
  String atResponse2 = _at.sendCommand(_connection, "AT+CSQ");
  String atResponse3 = _at.sendCommand(_connection, "ATH");

  _debugger.printLogLn("Setting up APN");
  _at.sendCommand(_connection, "AT+SAPBR=3,1,\"Contype\",\"GPRS\"");
  _at.sendCommand(_connection, "AT+SAPBR=3,1,\"APN\",\"" + apn + "\"");
  _at.sendCommand(_connection, "AT+SAPBR=3,1,\"USER\",\"" + username + "\"");
  _at.sendCommand(_connection, "AT+SAPBR=3,1,\"PWD\",\"" + password + "\"");

  _debugger.printLogLn("Enabling bearer");
  String atResponse = _at.sendCommand(_connection, "AT+SAPBR=1,1");
  String atResponse4 = _at.sendCommand(_connection, "AT+SAPBR=2,1");

  _gsmEnabled = true;

  return _at.isOk(atResponse4) && _at.isOk(atResponse2) && _at.isOk(atResponse3);
}

bool Sim808::enableGps()
{
  _debugger.printLogLn("Enabling GPS");
  _debugger.printLogLn("Powering on GPS");
  String atResponse = _at.sendCommand(_connection, "AT+CGNSPWR=1");
  _debugger.printLogLn("Define the NMEA Data Output Control");
  String atResponse2 = _at.sendCommand(_connection, "AT+CGPSOUT=32"); 

  _gpsEnabled = true;

  return _at.isOk(atResponse) && _at.isOk(atResponse2);
}

TinyGPSLocation Sim808::getLocation()
{
  if(_gpsEnabled)
  {
    _debugger.printLogLn("Getting location");
  
    while (!_gps.location.isUpdated()) {
      while (_connection.available() > 0 && !_gps.location.isUpdated()) {
        int inByte = _connection.read();
        _gps.encode(inByte);
        char inChar = inByte;
        _debugger.printLog(String(inChar));
      }
    } 
  }

  return _gps.location;
}

bool Sim808::getAndSendLocationViaHttpGet(String url)
{
  TinyGPSLocation location = getLocation();
  String latitude = String(location.lat());
  String longitude = String(location.lng());

  url.replace("{lat}", latitude);
  url.replace("{lng}", longitude);

  String response1 = _at.sendCommand(_connection, "AT+HTTPINIT");
  String response2 = _at.sendCommand(_connection, "AT+HTTPPARA=\"CID\",1");
  String response3 = _at.sendCommand(_connection, "AT+HTTPPARA=\"URL\",\"" + url + "\"");
  String response4 = _at.sendCommand(_connection, "AT+HTTPACTION=0");
  String response5 = _at.sendCommand(_connection, "AT+HTTPREAD");
  String response6 = _at.sendCommand(_connection, "AT+HTTPTERM");

  return _at.isOk(response1)  && _at.isOk(response2) && _at.isOk(response3)  && _at.isOk(response4) && _at.isOk(response5) && _at.isOk(response6);;
}