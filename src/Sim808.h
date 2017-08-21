/*
  Sim808.h - Library for simplifying the usage of a Sim808 module.
  Created by Dean Martin, FrostAura Industries, August 14, 2017.

  Purchase module from https://www.aliexpress.com/item/SIM808-development-board-instead-of-908-GSM-GPRS-GPS-Bluetooth-SMS-module-to-send-data-procedures/32748301433.html?spm=a2g0s.9042311.0.0.sWTPVd
*/
#ifndef SIM_808_H
#define SIM_808_H

#include "Arduino.h"
#include "SoftwareSerial.h"
#include "TinyGPS++.h"
#include "string.h"
#include "DebugAssist.h"
#include "AtAssist.h"

class Sim808
{
  public:
    Sim808(int rxPin, int txPin);
    initialize(int baudRate, bool debug);
    bool enableGsm(String apn, String username = "", String password = "");
    bool enableGps();
    TinyGPSLocation getLocation();
  private:
    bool _debug;
    bool _gpsEnabled;
    bool _gsmEnabled;
    DebugAssist _debugger;
    AtAssist _at;
    SoftwareSerial _connection;
    TinyGPSPlus _gps;
};

#endif

