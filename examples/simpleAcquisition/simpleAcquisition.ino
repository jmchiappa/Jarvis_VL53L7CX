#include <wrapper_vl53l7cx.h>

#define VL53L7CX_PIN_LPn D2
#define VL53L7CX_PIN_RST D3
JARVIS_VL53L7CX Imageur(&Wire, VL53L7CX_PIN_LPn, VL53L7CX_PIN_RST);

uint8_t Imageurresolution = 16;
VL53L7CX_ResultsData ImageurmeasurementData;
  
void setup() {
  Serial.begin(115200);
  while(!Serial){;}
  Imageur.begin();
  Imageur.init_sensor();
  Imageur.vl53l7cx_off();
  Imageur.vl53l7cx_on();
  Imageur.vl53l7cx_set_resolution(16);
  Imageur.vl53l7cx_set_ranging_frequency_hz(60);
  Imageur.vl53l7cx_start_ranging();
}
 
void loop() {
  if (Imageur.isDataReady()) {
    Imageur.vl53l7cx_get_ranging_data(&ImageurmeasurementData);
    /* si une distance n'est pas valide, alors la distance vaut 32767 (max de int16) */
    for( uint8_t i=0 ; i<Imageurresolution ; i++) {
      if( ImageurmeasurementData.target_status[i]!=5 && ImageurmeasurementData.target_status[i]!=9 )
      ImageurmeasurementData.distance_mm[i] = 32767;
    }
    const uint32_t elapsedTime=millis();
    Serial.print("[2,2]:");
    Serial.println(ImageurmeasurementData.distance_mm[2 + 2 * Imageurresolution ],DEC);
  }
}