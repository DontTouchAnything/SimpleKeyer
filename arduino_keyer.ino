//W9GGG Keyer by Patrick Gawthrop
//This is hella bad code tbh

//Whenever I get around to using that hardware
#include <Keyboard.h>
#include <SevenSeg.h>

SevenSeg disp(2,3,4,5,6,7,8);

const int numOfDigits=3;
int digitPins[numOfDigits]={10,11,12};

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
unsigned long ditMillis= 0;
unsigned long dahMillis= 0;
unsigned long currentMillis = 0;
unsigned long time1= 0;
unsigned long time2= 0;
bool nextKey;
//Menu Stuff
int wpm = 25;
int elementDit;
unsigned long elementDah;
unsigned long delayDit;
unsigned long delayDah;
int toneOut = 800;
int menuItem;
int menuActive = 0;
unsigned long activeTime;
unsigned long lastPress;
bool reverse = false;
bool polarSwitch = false;


void setup() {
//7 Setment Hookup in 43905830495385 years
  disp.setDigitPins(numOfDigits, digitPins);

//Setting up moar buddins  
  pinMode(DIT, INPUT);
  pinMode(DAH, INPUT);
  pinMode(PUSH, INPUT);
  digitalWrite(DIT, HIGH);
  digitalWrite(DAH, HIGH);
  digitalWrite(PUSH, HIGH);

//CW Speed: Elements = 1200/WPM. Dit is 1 element. Dah is 3 elements. The pause must be the sent signal + one element.
  elementDit = (1200 / (wpm));
  elementDah = ((elementDit) * 3);
  delayDit = ((elementDit) * 2);
  delayDah = ((elementDah) + (elementDit));

//Innefficient way to check if you should key or not. 
  currentMillis = millis();
  time1 = (currentMillis - (ditMillis - delayDit));
  time2 = (currentMillis - (dahMillis - delayDah));
  nextKey = true;
//TOT Timer  
  activeTime = (millis() - lastPress); 

}

void loop() {

//Dit and Dahs   
  if(polarSwitch = true)
  {
    if(digitalRead(DIT) == HIGH)
    {
      if((time1 && time2) >= 0)
      {
        if(reverse = true)
        {
          tone(BEEP, toneOut, elementDah);
          dahMillis = millis();
        }
        else
        {
          tone(BEEP, toneOut, elementDit);
        }
      }
    }
    if(digitalRead(DAH) == HIGH)
    {
      if((time1 && time2) >= 0)
      {
        if(reverse = true)
        {
          tone(BEEP, toneOut, elementDit);
        }
        else
        {
          tone(BEEP, toneOut, elementDah);
        }
      }
    }
  }
  else
  {
    if(digitalRead(DIT) == LOW)
    {
      if((time1 && time2) >= 0)
      {
        if(reverse = true)
        {
          tone(BEEP, toneOut, elementDah);
          dahMillis = millis();
        }  
        else
        {
          tone(BEEP, toneOut, elementDit);
          ditMillis = millis();
        }
      }  
    }
    if(digitalRead(DAH) == LOW)
    {
      if((time1 && time2) >= 0) 
      {
        if(reverse = true)
        {
          tone(BEEP, toneOut, elementDit); 
          ditMillis = millis();
        }
        else
        {
          tone(BEEP, toneOut, elementDah); 
          dahMillis = millis();
        }
      }
    }  
  }

  knob = (float)(enc.read());
  
//https://youtu.be/poz6W0znOfk?t=3 I hate myself - This is the menu
  if(menuActive = 0)
  {
    if(digitalRead(PUSH) == LOW)
    {
      disp.write(menuItem);
      menuActive = 1;
      lastPress = millis();
    }
  }  
  if(menuActive = 1)
  {
    if(knob != old_knob)
    {
      if(knob > old_knob)
      {
        menuItem = (menuItem + 1);
        disp.write(menuItem);
        lastPress = millis(); 
      }
      else
      {
        menuItem = (menuItem - 1);
        disp.write(menuItem);
        lastPress = millis();
      }
    }    
    if(menuItem >= 4)
    {
      menuItem = 0; 
    }
    if(menuItem <= -1)
    {
      menuItem = 3;   
    }
    if(digitalRead(PUSH) == LOW)
    {
      if(activeTime >= 500)
      {
        menuActive = 2;
        lastPress = millis(); 
      }
    }
    if(activeTime >= 10000)
    {
      menuActive = 0;
      //insert the clear disp thing whenever I get my hardware assembled...
    }
  }
  if(menuActive = 2)
  {
    if(menuItem = 0)
    {
      disp.write(wpm);
      if(knob != old_knob)
      {
        if(knob > old_knob)
        {
          wpm = (wpm + 1);
          disp.write(elementDit);
          lastPress = millis();  
        }
        else
        {
          wpm = (wpm - 1);
          disp.write(elementDit);
          lastPress = millis();
        }
      }
      if(wpm <= 0)
      {
        wpm = 1;
      }
    }
    if(menuItem = 1)
    {
      disp.write(toneOut);
      if(knob != old_knob)
      {
        if(knob > old_knob)
        {
          toneOut = (toneOut + 10);
          disp.write(toneOut);
          lastPress = millis();  
        }
        else
        {
          toneOut = (toneOut - 10);
          disp.write(toneOut);
          lastPress = millis();
        }
      }
      if(toneOut <= 0)
      {
        toneOut = 10; 
      }
    }
//Woah the future! Come back soon to find out!    
    if(menuItem = 2)
    {
      if(knob != old_knob)
      {
        if(knob > old_knob)
        {
          reverse = true;
          disp.write(1);
          lastPress = millis();
        }
        else
        {
          reverse = false;
          disp.write(0);
          lastPress = millis();
        }
      }
    }
    if(menuItem = 3)
    { 
      polarSwitch = true;
      disp.write(1);
      lastPress = millis();

    }
    else
    {
      polarSwitch = false;
      disp.write(0);
      lastPress = millis();

    }  

    if(activeTime >= 5000)
    {
      menuActive = 1;
    }
  }
}

//I hate coding.
