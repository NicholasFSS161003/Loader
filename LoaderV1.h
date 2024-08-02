#include <stdint.h>
#include <Arduino.h>
#include <Servo.h>

class LoaderV1 {
private:
  uint8_t _init_value;
  uint8_t _servo_pin;
  uint8_t _buttonPin; 
  uint8_t _counter = 0;
  bool _isloaded = 0;
  bool _flag = 0;
  uint8_t _rdu_dist = 0;
  uint8_t _edge_load_dist;
public:
  LoaderV1(uint8_t servo_pin, uint8_t init_value, uint8_t buttonPin);
  void load(uint8_t init_dist, uint8_t rdu,uint8_t rdu_limit);
  bool isloaded();
  void reset_counter();
  void detect_LoadDist();
  void update();
};
