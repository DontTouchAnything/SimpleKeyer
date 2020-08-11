//W9GGG Keyer by Patrick Gawthrop
//This is hella bad code tbh

//Whenever I get around to using that hardware
#include <Keyboard.h>
#include "SevSeg.h"
SevSeg sevseg; 

//All buttons
#define DIT 19
#define DAH 18
#define PUSH 15
#define BEEP 14

//Future knob
#include <Encoder.h>
Encoder enc(17, 16);
float knob = 0;
float old_knob = 0;

//CW Elements Setup
unsigned long ditMillis = 0;
unsigned long dahMillis = 0;
unsigned long currentMillis = 0;
unsigned long time1 = 0;
unsigned long time2 = 0;
bool nextKey;

void setup() {
//7 Setment Hookup in 43905830495385 years
  byte numDigits = 3;
  byte digitPins[] = {10, 11, 12};
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
  bool resistorsOnSegments = true;
  bool updateWithDelaysIn = true;
  byte hardwareConfig = COMMON_CATHODE;
  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments);
  sevseg.setBrightness(60);

//Setting up moar buddins  
  pinMode(DIT, INPUT);
  pinMode(DAH, INPUT);
  pinMode(PUSH, INPUT);
  digitalWrite(DIT, HIGH);
  digitalWrite(DAH, HIGH);
  digitalWrite(PUSH, HIGH);

//idk  
  Keyboard.begin();

//The CW Elements time thingy. Elements are 1200/WPM. 25WPM: Dit is 48ms, therefore needs 2 elements of cooldown. Dah is 3 elements 3*48 = 144ms. Therefore it needs 4 elements of cooldown.
  currentMillis = millis();
  time1 = (currentMillis - (ditMillis - 96));
  time2 = (currentMillis - (dahMillis - 192));
  nextKey = true;
}

void loop() {

//If there is time left on the delay between elements, nextKey will be false.
  if((time1 && time2) >= 0) 
  {
     nextKey = true;
    }
    else 
    {
     nextKey = false;
    }

//last digit of tone is the duration of the dah and dit.    
  if(digitalRead(DIT) == LOW)
  {
    if (nextKey = false) {
      tone(BEEP, 800, 48);
      ditMillis = millis();
    }
  }

  if(digitalRead(DAH) == LOW)
  {
    if (nextKey = false) {
      tone(BEEP, 800, 144); 
      dahMillis = millis();
    }
  }

}

//I hate coding.
