#pragma once
#include <Arduino.h>
#include <Servo.h>


class LoaderV1:public Servo {

private:
  uint8_t _init_value;
  uint8_t _servo_pin;
  uint8_t _buttonPin; 
  uint8_t _counter = 0,_counter2=0;
  bool _isloaded = 1;
  bool _LoadFlag = 0;
  uint8_t _rdu_dist = 0;
  uint8_t _edge_load_dist, _init_dist;
  uint8_t _rdu,_rdu_limit,_change;  
  double _frontVal;
  double _frontAng = _edge_load_dist;
  unsigned long lastDebounceTime = millis();

public:
  LoaderV1(uint8_t servo_pin, uint8_t buttonPin, uint8_t init_value);
  void load(uint8_t edge_load_dist,uint8_t _rdu,uint8_t rdu_dist,double _frontVal);
  bool isloaded();
  void setServo(uint8_t angle);
  void reset();
  int detect_LoadDist();
  void update();
};
