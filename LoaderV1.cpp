#include "LoaderV1.h"

LoaderV1::LoaderV1(uint8_t servo_pin, uint8_t buttonPin, uint8_t init_value)
  : _servo_pin(servo_pin), _buttonPin(buttonPin), _init_value(init_value) {
  pinMode(_buttonPin, INPUT_PULLUP);
  setServo(_init_value);
}

void LoaderV1::load(uint8_t edge_load_dist,uint8_t rdu,uint8_t rdu_dist,double frontVal){
 _edge_load_dist = edge_load_dist;
 _rdu = rdu;
 _rdu_dist = rdu_dist;
 _frontVal = frontVal; 
  _isloaded = 0;
  _frontAng = edge_load_dist;
  // if(_counter2 >= counter2_limit)
  //   _counter2 = counter2_limit;
}

bool LoaderV1::isloaded() {
  return _isloaded;
}

void LoaderV1::reset() {
  _counter = 0;
  setServo(_init_value);
}

// int LoaderV1::detect_LoadDist(){
//   if (digitalRead(_buttonPin)==1){
//     _edge_load_dist -= 2;
//   }
//  return _edge_load_dist;
// }

void LoaderV1::update() {
  unsigned long currentDebounceTime = millis();
  if(_isloaded == 0) {
    if (digitalRead(_buttonPin) == 0 && _frontAng <130 && _frontAng>30) {
      setServo(_frontAng); //going front
       _frontAng -= _frontVal;
       //_counter2 += change;
    } else  if(digitalRead(_buttonPin) == 1){
      if (lastDebounceTime - currentDebounceTime >= 50){
      _LoadFlag = 0;
      //Serial.print(_rdu_dist);
      setServo(_rdu_dist); //going back  
      _rdu_dist-=_rdu;
    //  ++_counter; 
       _isloaded = 1;
        currentDebounceTime = lastDebounceTime; 
      }
    }

    // if (_rdu_dist >= rdu_limit) {
    //   _counter = rdu;
    // }
  }
}


void LoaderV1::setServo(uint8_t angle){
   if(angle < 25){
    angle = 30;
   }
   if(angle>130){
    angle =130;
   } 
   Serial.println(angle);
   write(angle);//normal Servo.write
}
