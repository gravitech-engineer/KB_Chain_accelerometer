#include "KB_3Axis_ACC.h"


KB_3Axis_ACC acl;


void setup(void) {

  Serial.begin(9600);
  Serial.println("KB Chain 3axis accelerometer click Test!!!");
  
  if (! acl.begin(0x18)) {   // I2C address default 0x18 OR 0x19
    Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("KB Chain 3axis accelerometer start!");
  
  acl.setRange(LIS3DH_RANGE_2_G);   // 2, 4, 8 or 16 G!
  
}


void loop() {
  int16_t adc;
  // read the ADCs
  adc = acl.readADC(1);                                   //  Get Analog from Channel 1
  Serial.print("ADC1:\t"); Serial.print(adc); 
  
  adc = acl.readADC(2);                                   //  Get Analog from Channel 2
  Serial.print("ADC2:\t"); Serial.print(adc);

  adc = acl.readADC(3);                                   //  Get Analog from Channel 3
  Serial.print("ADC3:\t"); Serial.print(adc);

  Serial.println();
  delay(200);
}