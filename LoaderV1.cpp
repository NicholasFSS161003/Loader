#pragma once
#include "LoaderV1.h"

Servo Servo;

LoaderV1::LoaderV1(uint8_t servo_pin, uint8_t buttonPin, uint8_t init_value)
  : _servo_pin(servo_pin), _buttonPin(buttonPin), _init_value(init_value), _edge_load_dist(init_value) {
  Servo.attach(_servo_pin);
  Servo.write(_init_value);
  pinMode(_buttonPin, INPUT_PULLUP);
  digitalWrite(_buttonPin, HIGH);
}

void LoaderV1::load(uint8_t edge_load_dist,uint8_t change,uint8_t counter2_limit) {
  _isloaded = 0;
  Servo.write(edge_load_dist-_counter2);
  _counter2 += change;
  if(_counter2 >= counter2_limit)
    _counter2 = counter2_limit;
}

bool LoaderV1::isloaded() {
  return _isloaded;
}

void LoaderV1::reset_counter() {
  _counter = 0;
  Servo.write(_init_value);
  _rdu_dist = _init_value;
}

void LoaderV1::detect_LoadDist(){
  while (digitalRead(_buttonPin)==1){
    _edge_load_dist += 2;
  }
}

void LoaderV1::update(uint8_t init_dist, uint8_t rdu, uint8_t rdu_limit) {
  if (_isloaded == 0) {
    if (digitalRead(_buttonPin) == 0 && _flag == 0) {
      Servo.write(init_dist - _rdu_dist);
      _rdu_dist += rdu;
      ++_counter;
      _isloaded = 1;
    } else if (digitalRead(_buttonPin) == 1 && _flag == 1) {
      _flag = 0;
    }
    if (_rdu_dist >= rdu_limit) {
      _counter = rdu;
    }
   }
}
