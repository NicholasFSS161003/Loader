#include "LoaderV1.h"
#include <Arduino.h>

#define button 2

bool load_flag = 0 ;
bool press_flag = 0;

LoaderV1 loader(9, 7, 100,70, 1.5, 2, 80);

void setup() {
  Serial.begin(9600);
  loader.attach(9);
  loader.reset();
  pinMode(button, INPUT_PULLUP);
  digitalWrite(button, HIGH);
  }

void loop() {
  loader.update();
  if (digitalRead(button) == 0 && press_flag == 0) {
    press_flag = 1; 
     loader.load();

  } else if (digitalRead(button) == 1 && press_flag == 1) {
    press_flag = 0;
  }
  //Serial.print("Loader status1:  ");
  //Serial.println(loader.isloaded());
  //Serial.println(digitalRead(2));
}
 
