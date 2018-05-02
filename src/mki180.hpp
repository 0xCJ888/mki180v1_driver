#ifndef __MKI180_HPP__
#define __MKI180_HPP__

#include "mbed.h"
/* Device Identification (Who am I) */
#define LIS3DHH_ID            0x11
#define LIS3DHH_WHO_AM_I      0x0F
/* Sensitivity */
#define LIS3DHH_FROM_LSB_TO_mg(LSB)   (float)((LSB * 76.0f) / 1000.0f)
#define LIS3DHH_FROM_LSB_TO_degC(LSB) (float)(((int16_t)LSB>>4) / 16.0f) + 25.0f
/* Register mapping */
#define LIS3DHH_OUT_X_L_XL    0x28
#define LIS3DHH_OUT_X_H_XL    0x29
#define LIS3DHH_OUT_Y_L_XL    0x2A
#define LIS3DHH_OUT_Y_H_XL    0x2B
#define LIS3DHH_OUT_Z_L_XL    0x2C
#define LIS3DHH_OUT_Z_H_XL    0x2D
#define LIS3DHH_REGISTER_READ  0x01 << 7  

#define ReadAddr 0x00 
typedef struct{
    uint16_t xda, yda, zda;
    float x, y, z;
}ThreeAxis;

class mki180{
    public:
        mki180();
        uint8_t getwhoami(void);
        void get3axisdata(ThreeAxis* threeAxis);
    private:
        SPI spi;
        DigitalOut cs;
        void writeReg(uint8_t pWrite);
        void readReg(uint8_t pRead, uint8_t* data);
        uint16_t readAxisReg(uint8_t hAddr, uint8_t lAddr);
        float fromLSB2mg(uint16_t LSB);
};

#endif