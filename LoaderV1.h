#pragma once
#include <Arduino.h>
#include <Servo.h>


class LoaderV1:public Servo {

private:
  uint8_t _init_value = 120;
  uint8_t _servo_pin;
  uint8_t _buttonPin; 
  uint8_t _rdu_dist = 96;
  uint8_t _edge_load_dist = 100;
  bool _isloaded = 1;
  bool _LoadFlag = 0;
  double _rdu = 1;  
  double _frontVal = 0.35;
  double _frontAng = _edge_load_dist;
  unsigned long _LastDelay = millis(),_CurrentDelay;
  unsigned long _currentDebounceTime = 0,_lastDebounceTime = millis();
  void setServo(uint8_t angle); //Servo.write
public:
  LoaderV1(uint8_t servo_pin, uint8_t buttonPin);
  void setInitAng(uint8_t init_value, uint8_t edge_load_dist, double frontVal, double rdu, uint8_t rdu_dist);
  void load(); //loading 1 ring
  bool isloaded(); //returns value of isloaded(if the loading operation is complete or not) 
  void reset(); //reset to init_angle(not required at init)
  void update();  //loop :)
};
