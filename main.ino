#include "LoaderV1.h"
#include <Arduino.h>

#define button 2

LoaderV1 loader(9, 7, 100);
bool flag = 0;
void setup() {
  Serial.begin(9600);
  loader.attach(9);
  loader.reset();
  pinMode(button, INPUT_PULLUP);
  digitalWrite(button, HIGH);
}
//130 25
void loop() {
  loader.update();
  if (digitalRead(button) == 0 ) {
    loader.load(70, 2, 66, 0.3);
  } else if (digitalRead(button) == 1) {
    
  }
  // Serial.print("Loader status1:  ");
  // Serial.println(loader.isloaded());
}
