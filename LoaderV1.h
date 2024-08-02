#pragma once
#include <Arduino.h>
#include <Servo.h>


class LoaderV1:public Servo {

private:
  uint8_t _init_value;
  uint8_t _servo_pin;
  uint8_t _buttonPin; 
  uint8_t _counter = 0,_counter2=0;
  bool _isloaded = 0;
  bool _flag = 0;
  uint8_t _rdu_dist = 0;
  uint8_t _edge_load_dist, _init_dist;
  
public:
  LoaderV1(uint8_t servo_pin, uint8_t buttonPin, uint8_t init_value);
  void load(uint8_t edge_load_dist,uint8_t change,uint8_t counter2_limit);
  bool isloaded();
  void setServo(uint8_t angle);
  void reset();
  void detect_LoadDist();
  void update(uint8_t init_dist, uint8_t rdu, uint8_t rdu_limit);
};
