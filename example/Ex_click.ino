#include "KB_3Axis_ACC.h"


#define CLICKTHRESHHOLD 80

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

  // 0 = turn off click 
  // 1 = single click 
  // 2 = double click 
  acl.setClick(2, CLICKTHRESHHOLD);
  delay(100);
}


void loop() {
  uint8_t click = acl.getClick();
  if (click == 0) return;
  if (! (click & 0x30)) return;
  Serial.print("Click detected (0x"); Serial.print(click, HEX); Serial.print("): ");
  if (click & 0x10) Serial.print(" single click");
  if (click & 0x20) Serial.print(" double click");
  Serial.println();

  delay(100);
  return;
}