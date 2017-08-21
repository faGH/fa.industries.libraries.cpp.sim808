#include "Sim808.h"
#include "DebugAssist.h"
#include "string.h"
#include "FastLED.h"
#include "TinyGPS++.h"

// System Configuration
#define DEBUG true
#define MODEM_RX 11
#define MODEM_TX 12
#define MODEM_BAUD_RATE 9600
#define DATA_TRANSMISSION_DELAY 10000
#define APN "internet"

// LED configuration
#define NUM_OF_LEDS 1
#define LED_DATA_PIN 4

CRGB leds[NUM_OF_LEDS];
DebugAssist debugger;
Sim808 modem(MODEM_RX, MODEM_TX);

void setup()
{
  debugger.initialize(DEBUG);
  modem.initialize(MODEM_BAUD_RATE, DEBUG);
  FastLED.addLeds<TM1804, LED_DATA_PIN, RGB>(leds, NUM_OF_LEDS);
  
  if(!modem.enableGsm(APN)) throwError("Failed to enable GSM", CRGB::Red, true);
  if(!modem.enableGps()) throwError("Failed to enable GPS", CRGB::Red, true);
}

void loop()
{
  debugger.printLogLn("Data transmission initializing");
  bool locationTransmissionSuccessful = modem.sendLocationToUrl("URL_WITH_PLACEHOLDERS")
  
  delay(DATA_TRANSMISSION_DELAY);
}

void throwError(String error, CRGB color, bool isCritical)
{
  debugger.printLogLn("Error thrown: '" + error + "'");
  notifyWithColor(500, color);

  if(isCritical) performHardReset();
}

void notifyWithColor(int timeout, CRGB color)
{
  debugger.printLogLn("Notifying via LED color change");
  leds[0] = color;
  FastLED.show();
  delay(timeout);
}

void performHardReset()
{
  debugger.printLogLn("Performing a hardware reset");
}
