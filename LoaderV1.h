#pragma once
#include <Arduino.h>
#include <Servo.h>


class LoaderV1:public Servo {

private:
  uint8_t _init_value;
  uint8_t _servo_pin;
  uint8_t _buttonPin; 
  bool _isloaded = 1;
  bool _LoadFlag = 0;
  uint8_t _rdu_dist,_rdu2_dist;
  uint8_t _edge_load_dist, _init_dist;
  double _rdu,_rdu2,_change;  
  double _frontVal;
  double _frontAng = _edge_load_dist;

  unsigned long _currentDebounceTime = 0,_lastDebounceTime = millis();

public:
  LoaderV1(uint8_t servo_pin, uint8_t buttonPin, uint8_t init_value,uint8_t edge_load_dist,double frontVal,double rdu,uint8_t rdu_dist);
  void load();
  bool isloaded();
  void setServo(uint8_t angle);
  void reset();
  void update();  
};
