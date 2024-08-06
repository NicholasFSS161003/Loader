#include "LoaderV1.h"
LoaderV1::LoaderV1(uint8_t servo_pin, uint8_t buttonPin, uint8_t init_value, uint8_t edge_load_dist, double frontVal, double rdu, uint8_t rdu_dist)
  : _servo_pin(servo_pin), _buttonPin(buttonPin), _init_value(init_value), _edge_load_dist(edge_load_dist), _rdu(rdu), _rdu_dist(rdu_dist), _frontVal(frontVal), _frontAng(edge_load_dist) {
  pinMode(_buttonPin, INPUT_PULLUP);
  setServo(_init_value);
}

void LoaderV1::load() {
  _currentDebounceTime = millis();

  _isloaded = 0;
}

bool LoaderV1::isloaded() {

  return _isloaded;
}

void LoaderV1::reset() {
  setServo(_init_value);
}

void LoaderV1::update() {
  if (_isloaded == 0) {
    if (digitalRead(_buttonPin) == 0 && _frontAng < 130 && _frontAng > 30) {
      setServo(_frontAng);  //going front
      _frontAng -= _frontVal;
    } else if (digitalRead(_buttonPin) == 1) {
      if (millis() - _currentDebounceTime >= 65) {
        _LoadFlag = 0;
        setServo(_rdu_dist);  //going back
        _rdu_dist -= _rdu;
        if (_rdu_dist <= 30)
          _rdu_dist = 30;
        Serial.print("update");
        Serial.print("\t");

        _isloaded = 1;
      }
    }
  }  //Serial.println(digitalRead(_buttonPin));
}

void LoaderV1::setServo(uint8_t angle) {
  if (angle < 25) {
    angle = 30;
  }
  if (angle > 130) {
    angle = 130;
  }
  write(angle);  //normal Servo.write
}
