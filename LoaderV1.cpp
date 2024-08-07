#include "LoaderV1.h"
LoaderV1::LoaderV1(uint8_t servo_pin, uint8_t buttonPin)
  : _servo_pin(servo_pin), _buttonPin(buttonPin) {
  pinMode(_buttonPin, INPUT_PULLUP);
  pinMode(_servo_pin, OUTPUT);
  attach(_servo_pin);
  setServo(_init_value);
}

void LoaderV1::setInitAng(uint8_t init_value, uint8_t edge_load_dist, double frontVal, double rdu, uint8_t rdu_dist) {  //Initializing all values of variables
  _init_value = init_value;
  _edge_load_dist = edge_load_dist;
  _rdu = rdu;
  _rdu_dist = rdu_dist;
  _frontVal = frontVal;
  _frontAng = edge_load_dist;
}

void LoaderV1::load() {
  _currentDebounceTime = millis();
  _isloaded = 0;
  _frontAng = _edge_load_dist;
}

bool LoaderV1::isloaded() {
  return _isloaded;
}

void LoaderV1::reset() {
  setServo(_init_value);
}

void LoaderV1::update() {
  if (_isloaded == 0) {

    if (digitalRead(_buttonPin) == 0) { 

      if (_frontAng > _rdu_dist) {
        //From init_dist to selected distance (speed up to not waste time)
        _frontAng -= 1;
      } else {
        //From selected distance to the shooter
        _CurrentDelay = millis();
        if (_CurrentDelay - _LastDelay >= 50) {
          _frontAng -= _frontVal;
          _LastDelay = _CurrentDelay;
        }
      }
      setServo(_frontAng);  //going front
    } else if (digitalRead(_buttonPin) == 1) {
      if (_lastDebounceTime - _currentDebounceTime >= 5) {  //Debounce(To prevent the hit button being activated by the shaking)

        setServo(_rdu_dist);  //going back
        _rdu_dist -= _rdu;

        if (_rdu_dist <= 30)  //set a safe limit
          _rdu_dist = 30;

        _lastDebounceTime = _currentDebounceTime;
        _isloaded = 1;
      }
    }
  }
}

void LoaderV1::setServo(uint8_t angle) {
  angle = constrain(angle, 30, 130);  //safety  limit
  write(angle);                       //normal Servo.write
}
