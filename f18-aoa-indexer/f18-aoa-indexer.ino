/*
  f18-aoa-indexer
  Designed for use (misuse!) on the 30 Days Lost in Space Kit hardware: https://inventr.io/product/adventure-kit-30-days-lost-in-space/
  See the YouTube video: https://www.youtube.com/watch?v=mQyqUskZiT4
  Part of this GitHub repository: https://github.com/agentcox/dcs-arduino-builds
  Get DCS-Bios here: http://dcs-bios.a10c.de/
  Tinkercad of this design is here: https://www.tinkercad.com/things/cb8hnYoisas-fa-18c-aoa-indexer-for-dcs-bios
 */
#define DCSBIOS_IRQ_SERIAL

#include "DcsBios.h"

const int greenLight = 13;
const int yellowLight = 12;
const int redLight = 11;

DcsBios::LED aoaIndexerHigh(0x7408, 0x0008, greenLight);
DcsBios::LED aoaIndexerNormal(0x7408, 0x0010, yellowLight);
DcsBios::LED aoaIndexerLow(0x7408, 0x0020, redLight);

void setup() {
  DcsBios::setup();
}

void loop() {
  DcsBios::loop();
}
