#include "Arduino.h"
#include "Wire.h"


#define Gravity                  9.80665

//=========================================================================
//                           I2C ADDRESS/BITS
//_________________________________________________________________________
//
#define LIS3DH_DEFAULT_ADDRESS  (0x18)    //  OR 0x19
//
//=========================================================================

#define LIS3DH_REG_STATUS1       0x07
#define LIS3DH_REG_OUTADC1_L     0x08
#define LIS3DH_REG_OUTADC1_H     0x09
#define LIS3DH_REG_OUTADC2_L     0x0A
#define LIS3DH_REG_OUTADC2_H     0x0B
#define LIS3DH_REG_OUTADC3_L     0x0C
#define LIS3DH_REG_OUTADC3_H     0x0D
#define LIS3DH_REG_INTCOUNT      0x0E
#define LIS3DH_REG_WHOAMI        0x0F
#define LIS3DH_REG_TEMPCFG       0x1F
#define LIS3DH_REG_CTRL1         0x20
#define LIS3DH_REG_CTRL2         0x21
#define LIS3DH_REG_CTRL3         0x22
#define LIS3DH_REG_CTRL4         0x23
#define LIS3DH_REG_CTRL5         0x24
#define LIS3DH_REG_CTRL6         0x25
#define LIS3DH_REG_REFERENCE     0x26
#define LIS3DH_REG_STATUS2       0x27
#define LIS3DH_REG_OUT_X_L       0x28
#define LIS3DH_REG_OUT_X_H       0x29
#define LIS3DH_REG_OUT_Y_L       0x2A
#define LIS3DH_REG_OUT_Y_H       0x2B
#define LIS3DH_REG_OUT_Z_L       0x2C
#define LIS3DH_REG_OUT_Z_H       0x2D
#define LIS3DH_REG_FIFOCTRL      0x2E
#define LIS3DH_REG_FIFOSRC       0x2F
#define LIS3DH_REG_INT1CFG       0x30
#define LIS3DH_REG_INT1SRC       0x31
#define LIS3DH_REG_INT1THS       0x32
#define LIS3DH_REG_INT1DUR       0x33
#define LIS3DH_REG_CLICKCFG      0x38
#define LIS3DH_REG_CLICKSRC      0x39
#define LIS3DH_REG_CLICKTHS      0x3A
#define LIS3DH_REG_TIMELIMIT     0x3B
#define LIS3DH_REG_TIMELATENCY   0x3C
#define LIS3DH_REG_TIMEWINDOW    0x3D
#define LIS3DH_REG_ACTTHS        0x3E
#define LIS3DH_REG_ACTDUR        0x3F


typedef enum
{
  LIS3DH_RANGE_16_G         = 0x3,   // +/- 16g
  LIS3DH_RANGE_8_G           = 0x2,   // +/- 8g
  LIS3DH_RANGE_4_G           = 0x1,   // +/- 4g
  LIS3DH_RANGE_2_G           = 0x0    // +/- 2g (default value)
} lis3dh_range_t;

typedef enum
{
  LIS3DH_AXIS_X         = 0x0,
  LIS3DH_AXIS_Y         = 0x1,
  LIS3DH_AXIS_Z         = 0x2,
} lis3dh_axis_t;


// register 0x2A (LIS3DH_REG_CTRL_REG1) to set bandwidth 
typedef enum
{
  LIS3DH_DATARATE_400_HZ     = 0x07, //  400Hz
  LIS3DH_DATARATE_200_HZ     = 0x06, //  200Hz
  LIS3DH_DATARATE_100_HZ     = 0x05, //  100Hz
  LIS3DH_DATARATE_50_HZ      = 0x04, //   50Hz
  LIS3DH_DATARATE_25_HZ      = 0x03, //   25Hz
  LIS3DH_DATARATE_10_HZ      = 0x02, // 10 Hz
  LIS3DH_DATARATE_1_HZ       = 0x01, // 1 Hz
  LIS3DH_DATARATE_POWERDOWN  = 0x0,
  LIS3DH_DATARATE_LOWPOWER_1K6HZ  = 0x08,
  LIS3DH_DATARATE_LOWPOWER_5KHZ  =  0x09,

} lis3dh_dataRate_t;

class KB_3Axis_ACC
{
  public:
    

    bool begin(uint8_t addr = LIS3DH_DEFAULT_ADDRESS);

    void read();
    int16_t readADC(uint8_t channal);

    void setDataRate(lis3dh_dataRate_t dataRate);
    void setRange(lis3dh_range_t range);

    lis3dh_dataRate_t getDataRate(void);
    lis3dh_range_t getRange(void);
    uint8_t getDeviceId();

    void setClick(uint8_t c, uint8_t clickthresh, uint8_t timelimit = 10, uint8_t timelatency = 20, uint8_t timewindow = 255);
    uint8_t getClick(void);

    int16_t getRawAxisX();
    int16_t getRawAxisY();
    int16_t getRawAxisZ();


    float getAxisX();
    float getAxisY();
    float getAxisZ();

  private:
    int16_t x, y, z;
    float x_g, y_g, z_g;


    void writeRegister(uint8_t reg, uint8_t value);
    uint8_t readRegister(uint8_t reg);

    uint8_t _i2caddress;

};
