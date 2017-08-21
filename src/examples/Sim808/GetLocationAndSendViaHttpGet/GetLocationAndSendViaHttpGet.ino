#include "Sim808.h"

#define DEBUG true
#define MODEM_RX 11
#define MODEM_TX 12
#define MODEM_BAUD_RATE 9600
#define APN "internet"

Sim808 modem(MODEM_RX, MODEM_TX);

void setup() {
  modem.initialize(MODEM_BAUD_RATE, DEBUG);

  if(!modem.enableGsm(APN)) throwError("Failed to enable GSM");
  if(!modem.enableGps()) throwError("Failed to enable GPS");
}

void loop() {
  bool locationTransmissionSuccessful = modem.getAndSendLocationViaHttpGet("URL_WITH_PLACEHOLDERS");

  delay(1000);
}

void throwError(String error)
{ }
