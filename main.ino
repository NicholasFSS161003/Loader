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

void loop() {
    loader.load(90,2,30);
 if(digitalRead(button)==0 && flag ==0){
  loader.update(60,2,30);

   flag = 1;
  }else if(digitalRead(button)==1 && flag ==1){
    flag = 0;
  }
    Serial.print("Loader status1:  ");
  Serial.println(loader.isloaded());

}
