#include "LoaderV1.h"
#include <Arduino.h>

#define button 2

bool load_flag = 0;
bool press_flag = 0;

LoaderV1* loader;

void setup() {
  Serial.begin(9600);
  
  loader = &LoaderV1(9, 7);

  pinMode(button, INPUT_PULLUP);
}

void loop() {
  loader->update();

  if (loader->isloaded() == 1) {
    if (digitalRead(button) == 0 && press_flag == 0) {
      press_flag = 1;  // Instant Debounce
      loader->load();
    } else if (digitalRead(button) == 1 && press_flag == 1) {
      press_flag = 0;
    }
  }
}

