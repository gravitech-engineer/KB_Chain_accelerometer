#include "KB_3Axis_ACC.h"

KB_3Axis_ACC acl;
void setup() {
  Serial.begin(9600);
  acl.begin(0x18);                                              //  Initial I2C address default 0x18 OR 0x19
  acl.setRange(LIS3DH_RANGE_16_G);                              //  Set G range
  acl.setDataRate(LIS3DH_DATARATE_200_HZ);                      //  Set data rate 
}

void loop() {
  acl.read();
  Serial.println("===========================   ACC RAW   =============================");
  Serial.print(acl.getRawAxisX()); Serial.print('\t');          //  Get raw Axis X
  Serial.print(acl.getRawAxisY()); Serial.print('\t');          //  Get raw Axis Y
  Serial.println(acl.getRawAxisZ());                            //  Get raw Axis Z
  Serial.println("---------------------------   ACC CAL   -----------------------------");
  Serial.print(acl.getAxisX()); Serial.print('\t');             //  Get cal Axis X
  Serial.print(acl.getAxisY()); Serial.print('\t');             //  Get cal Axis Y
  Serial.println(acl.getAxisZ());                               //  Get cal Axis Z
  Serial.println("=====================================================================");
  delay(500);
}