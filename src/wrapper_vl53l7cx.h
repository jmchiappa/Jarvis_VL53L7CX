#ifndef WRAPPER_VL53L7CX
#define WRAPPER_VL53L7CX

#include <Arduino.h>
#include <Wire.h>
#include <vl53l7cx_class.h>

class JARVIS_VL53L7CX : public VL53L7CX {
  using VL53L7CX::VL53L7CX;
  public:
    uint8_t isDataReady() {
      uint8_t NewDataReady = 0;
      uint8_t status;
      status = this->vl53l7cx_check_data_ready(&NewDataReady);
      if (status == 0)
        return NewDataReady != 0;
      return false;
    }

    uint8_t getResolution() {
      uint8_t res;
      this->vl53l7cx_get_resolution(&res);
      return res;
    }
};
#endif