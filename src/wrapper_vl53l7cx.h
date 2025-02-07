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

    void setResolution(uint8_t res) {
      this->vl53l7cx_set_resolution(res);
      this->resolution = res;
    }

    uint8_t getResolution() {
      if(this->resolution == 0) {
        uint8_t status = this->vl53l7cx_get_resolution(&resolution);
        if(status == 0 && resolution == 0 ) {
          return 16;
        }
      }
      return this->resolution;
    }

    uint8_t nbRow() {
      uint8_t res = getResolution();
      return res==16 ? 4 : 8;
    }

  private:
    uint8_t resolution = 0;
};
#endif