#include <ELM327.h>
#include "FastLED.h"

#define NUM_LEDS 6
#define DATA_PIN 4

#define MinRevs 500
#define StallRevs 700
#define CruiseRevs 1500
#define TorqueRevs 3000
#define ShiftRevs 5000
#define MaxRevs  6000

#define OffColor CRGB::Black

uint8_t Brightness = 255;

CRGB leds[NUM_LEDS];

Elm327 ELM;

void SetStrip(CRGB Color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = Color;
  }
  FastLED.show();
}

void CheckStrip(int Delay) {
  SetStrip(CRGB::Red);
  delay(Delay);
  SetStrip(CRGB::Black);
  delay(Delay);
  SetStrip(CRGB::Green);
  delay(Delay);
  SetStrip(CRGB::Black);
  delay(Delay);
  SetStrip(CRGB::Blue);
  delay(Delay);
  SetStrip(CRGB::Black);
  delay(Delay);
}

void FlashDelay(CRGB Color, int Loops, int Delay) {
  for (int i = 0; i < Loops; i++) {
    SetStrip(Color);
    delay(Delay);
    SetStrip(CRGB::Black);
    delay(Delay);
  }
}

void setup() {
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  FastLED.setBrightness(Brightness);
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  SetStrip(CRGB::White);
  while (ELM.begin() != ELM_SUCCESS) {
    delay(1000);
  }
  SetStrip(CRGB::Black);
  digitalWrite(13, LOW);
  //loop will begin as soon as ELM connects
}

int RPM = 750;
long LastStallChange = 0;

//Stall Alarm
bool LastStallState = false;
#define MinStallFlash 20
#define MaxStallFlash 100
#define StallColor CRGB::Red
#define StallColor2 CRGB::Black
//Shift Indicator
long LastShiftChange = 0;
bool LastShiftState = false;
#define MinShiftFlash 20
#define MaxShiftFlash 100
#define ShiftColor2 CRGB::Black
void RevStrip(int Revs) {
  if (Revs <= MinRevs || Revs > MaxRevs) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = OffColor;
    }
  }  
  if (Revs > MinRevs && Revs <= StallRevs) {
    int FlashInterval = map(Revs, MinRevs, StallRevs, MinStallFlash, MaxStallFlash);
    FlashInterval < MinStallFlash ? FlashInterval = MinStallFlash : true;
    if (LastStallState == true) {
      if (millis() > (LastStallChange + FlashInterval)) {
        //turn off leds and buzzer
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = StallColor2;    
        }
        LastStallState = false;
        LastStallChange = millis();
      }
    } else {
      if (millis() > (LastStallChange + FlashInterval)) {
        //turn on leds and buzzer
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CRGB::StallColor;
        }
        LastStallState = true;
        LastStallChange = millis();
      }
    }  
  }
  if (Revs > StallRevs && Revs <= ShiftRevs) {
    for (int i = 0; i < map(Revs, StallRevs, ShiftRevs, 1, NUM_LEDS); i++) {
      leds[i] = CHSV(map(i, 0, NUM_LEDS - 1, 96, -96), 255, 255);
    }
    for (int i = map(Revs, StallRevs, ShiftRevs, 1, NUM_LEDS); i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
    }
  }
  if (Revs > ShiftRevs && Revs <= MaxRevs) {
    int FlashInterval = map(Revs, ShiftRevs, MaxRevs, MaxShiftFlash, MinShiftFlash);
    FlashInterval < MinShiftFlash ? FlashInterval = MinShiftFlash : true;
    if (LastShiftState == true) {
      if (millis() > (LastShiftChange + FlashInterval)) {
        //turn off leds and buzzer
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = ShiftColor2;
        }
        LastShiftState = false;
        LastShiftChange = millis();
      }
    } else {
      if (millis() > (LastShiftChange + FlashInterval)) {
        //turn on leds and buzzer
        for (int i = 0; i < NUM_LEDS; i++) {
          leds[i] = CHSV(map(i, 0, NUM_LEDS - 1, 96, -96), 255, 255);
        }
        LastShiftState = true;
        LastShiftChange = millis();
      }
    } 
  }
  FastLED.show();
}

void loop() {
  unsigned long T = millis();
  byte Tmp = ELM.engineRPM(RPM);
  if (Tmp == ELM_SUCCESS) {
    RevStrip(RPM);
    DEBUG_SERIAL.println((String)"RPM: " + RPM + " TIME: " + (millis() - T));
  }
  //delay(50);
}
