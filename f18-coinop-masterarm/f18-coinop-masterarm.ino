
#define DCSBIOS_DEFAULT_SERIAL

#include "DcsBios.h"

const int lightPin = 10; //wire up a light to show coin timer running
const int coinPin = 2; //needs to be either 2 or 1 for digital interrupt, remember to ground it
const int timerMax = 5000; //5 seconds, set to what you like
const int coinPulseThreshold = 5; //set to your pulse # on your coin acceptor

int timerLeft = 0; 
bool timerActive = false;

unsigned long nowTime;
unsigned long lastTime;
unsigned long timeDiff;

volatile int coinPulses = 0; //can only have 8 bits volatile, rest processed outside interrupt.

void setup() {
  pinMode(lightPin, OUTPUT);
  pinMode(coinPin, INPUT_PULLUP); //coin pin needs to be a pull-up

  attachInterrupt(digitalPinToInterrupt(coinPin), coinPulse, FALLING); //pull-up reverses high and low, so measure falling.

  DcsBios::setup();
  lastTime = millis();
}

//this is run every time there's a signal on the coin pin.
//can only process 8 bits of info reliably, so must be one int max.
void coinPulse(){
  coinPulses = coinPulses + 1;
}

void timerStart(){
  timerLeft = timerMax;
  timerActive = true;
}

void timeExpired(){
  timerLeft = 0;
  timerActive = false;
}

void loop() {
  nowTime = millis();
  timeDiff = nowTime - lastTime;
  
  DcsBios::loop();

  if(coinPulses >= coinPulseThreshold){
   timerStart();
   coinPulses = 0;
  }
  
  if(timerActive == true){
    digitalWrite(lightPin, HIGH);
    DcsBios::sendDcsBiosMessage("MASTER_ARM_SW", "1"); //f18 master arm ON
    
    timerLeft = timerLeft - timeDiff;
    if(timerLeft <= 0){
      timeExpired();
    }
  } 
  else{
    digitalWrite(lightPin, LOW);
    DcsBios::sendDcsBiosMessage("MASTER_ARM_SW", "0"); //f18 master arm OFF
  }

  lastTime = nowTime;
}
