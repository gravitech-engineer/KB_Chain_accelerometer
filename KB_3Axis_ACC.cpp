#include "KB_3Axis_ACC.h"



bool KB_3Axis_KB_ACC::begin(uint8_t i2caddr) {
  _i2caddress = i2caddr;
  Wire.begin(4, 5);

  
  uint8_t deviceid = readRegister(LIS3DH_REG_WHOAMI);
  if (deviceid != 0x33)
  {
    return false;
  }

  
  writeRegister(LIS3DH_REG_CTRL1, 0x07);
  setDataRate(LIS3DH_DATARATE_400_HZ);
  writeRegister(LIS3DH_REG_CTRL4, 0x88);
  writeRegister(LIS3DH_REG_CTRL3, 0x10);
  //writeRegister(LIS3DH_REG_PL_CFG, 0x40);
  writeRegister(LIS3DH_REG_TEMPCFG, 0x80);
  return true;
}


void KB_3Axis_ACC::read(void) {
  Wire.beginTransmission(_i2caddress);
  Wire.write(LIS3DH_REG_OUT_X_L | 0x80); // 0x80 for autoincrement
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)_i2caddress, (uint8_t)6);
  x = Wire.read(); x |= ((uint16_t)Wire.read()) << 8;
  y = Wire.read(); y |= ((uint16_t)Wire.read()) << 8;
  z = Wire.read(); z |= ((uint16_t)Wire.read()) << 8;


  uint8_t range = getRange();
  uint16_t divider = 1;
  if (range == LIS3DH_RANGE_16_G) divider = 1365; // different sensitivity at 16g
  if (range == LIS3DH_RANGE_8_G) divider = 4096;
  if (range == LIS3DH_RANGE_4_G) divider = 8190;
  if (range == LIS3DH_RANGE_2_G) divider = 16380;
  x_g = (float)x / divider;
  y_g = (float)y / divider;
  z_g = (float)z / divider;

}


int16_t KB_3Axis_ACC::readADC(uint8_t adc) {
  if ((adc < 1) || (adc > 3)) return 0;
  uint16_t value;

  adc--;

  uint8_t reg = LIS3DH_REG_OUTADC1_L + adc * 2;

  Wire.beginTransmission(_i2caddress);
  Wire.write(reg | 0x80);   // 0x80 for autoincrement
  Wire.endTransmission();
  Wire.requestFrom((uint8_t)_i2caddress, (uint8_t)2);
  value = Wire.read();  value |= ((uint16_t)Wire.read()) << 8;



  return value;
}

void KB_3Axis_ACC::setClick(uint8_t c, uint8_t clickthresh, uint8_t timelimit, uint8_t timelatency, uint8_t timewindow) {
  if (!c) {
    uint8_t r = readRegister(LIS3DH_REG_CTRL3);
    r &= ~(0x80);
    writeRegister(LIS3DH_REG_CTRL3, r);
    writeRegister(LIS3DH_REG_CLICKCFG, 0);
    return;
  }
  writeRegister(LIS3DH_REG_CTRL3, 0x80);
  writeRegister(LIS3DH_REG_CTRL5, 0x08); 

  if (c == 1)
    writeRegister(LIS3DH_REG_CLICKCFG, 0x15);
  if (c == 2)
    writeRegister(LIS3DH_REG_CLICKCFG, 0x2A);


  writeRegister(LIS3DH_REG_CLICKTHS, clickthresh);
  writeRegister(LIS3DH_REG_TIMELIMIT, timelimit);
  writeRegister(LIS3DH_REG_TIMELATENCY, timelatency);
  writeRegister(LIS3DH_REG_TIMEWINDOW, timewindow);
}

uint8_t KB_3Axis_ACC::getClick(void) {
  return readRegister(LIS3DH_REG_CLICKSRC);
}



void KB_3Axis_ACC::setRange(lis3dh_range_t range)
{
  uint8_t r = readRegister(LIS3DH_REG_CTRL4);
  r &= ~(0x30);
  r |= range << 4;
  writeRegister(LIS3DH_REG_CTRL4, r);
}


lis3dh_range_t KB_3Axis_ACC::getRange(void)
{
  return (lis3dh_range_t)((readRegister(LIS3DH_REG_CTRL4) >> 4) & 0x03);
}

void KB_3Axis_ACC::setDataRate(lis3dh_dataRate_t dataRate)
{
  uint8_t ctl1 = readRegister(LIS3DH_REG_CTRL1);
  ctl1 &= ~(0xF0);
  ctl1 |= (dataRate << 4);
  writeRegister(LIS3DH_REG_CTRL1, ctl1);
}


lis3dh_dataRate_t KB_3Axis_ACC::getDataRate(void)
{
  return (lis3dh_dataRate_t)((readRegister(LIS3DH_REG_CTRL1) >> 4) & 0x0F);
}


int16_t KB_3Axis_ACC::getRawAxisX() {
  return x;
}
int16_t KB_3Axis_ACC::getRawAxisY() {
  return y;
}
int16_t KB_3Axis_ACC::getRawAxisZ() {
  return z;
}


float KB_3Axis_ACC::getAxisX() {
  return x_g;
}
float KB_3Axis_ACC::getAxisY() {
  return y_g;
}
float KB_3Axis_ACC::getAxisZ() {
  return z_g;
}

void KB_3Axis_ACC::writeRegister(uint8_t reg, uint8_t value) {

  Wire.beginTransmission((uint8_t)_i2caddress);
  Wire.write((uint8_t)reg);
  Wire.write((uint8_t)value);
  Wire.endTransmission();

}


uint8_t KB_3Axis_ACC::readRegister(uint8_t reg) {
  uint8_t value;

  Wire.beginTransmission(_i2caddress);
  Wire.write((uint8_t)reg);
  Wire.endTransmission();

  Wire.requestFrom((uint8_t)_i2caddress, (uint8_t)1);
  value = Wire.read();

  return value;
}