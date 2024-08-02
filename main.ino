#include "LoaderV1.h"

#define button 7

LoaderV1 loader(9, 2, 100);
bool flag = 0;

void setup() {
  pinMode(button, INPUT_PULLUP);
  digitalWrite(button, HIGH);
}

void loop() {
  if(digitalRead(button)==0 && flag ==0){
  loader.update(60,2,30);
   flag = 1;
  }else if(digitalRead(button)==1 && flag ==1){
    flag = 0;
  }

  loader.load(90,2,30);
  
  Serial.print("Loader status: ");
  Serial.println(loader.isloaded());
}
