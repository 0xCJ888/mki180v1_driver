#include "mki180.hpp"

mki180::mki180():spi(SPI_MOSI, SPI_MISO, SPI_SCK),
                 cs(D0){
    spi.format(8,3);
    spi.frequency(500000);
}

void mki180::writeReg(uint8_t pWrite){
    cs = 1;
    cs = 0;
    spi.write(pWrite);
}

void mki180::readReg(uint8_t pRead, uint8_t* data){
     *data = spi.write(pRead);
}

void mki180::setCTRL_REG1(uint8_t pWrite, uint8_t pRead){
    cs = 1;
    cs = 0;
    spi.write(pWrite);
    spi.write(pRead);
}

uint16_t mki180::readAxisReg(uint8_t hAddr, uint8_t lAddr){
    uint8_t MSB;
    uint8_t LSB;
    this->writeReg(hAddr);
    this->readReg(ReadAddr, &MSB);
    this->writeReg(lAddr);
    this->readReg(ReadAddr, &LSB);
    return MSB << 8 | LSB;
}

float mki180::fromLSB2mg(uint16_t LSB){
    return LIS3DHH_FROM_LSB_TO_mg(LSB) - 2500; 
}

uint8_t mki180::getwhoami(void){
    uint8_t whoami;
    this->writeReg(LIS3DHH_WHO_AM_I | LIS3DHH_REGISTER_READ);
    this->readReg(ReadAddr, &whoami);
    return whoami;
}

void mki180::get3axisdata(ThreeAxis* threeAxis){
    threeAxis->xda = this->readAxisReg(LIS3DHH_OUT_X_H_XL | LIS3DHH_REGISTER_READ, LIS3DHH_OUT_X_L_XL | LIS3DHH_REGISTER_READ);
    threeAxis->x = this->fromLSB2mg(threeAxis->xda);
    threeAxis->yda = this->readAxisReg(LIS3DHH_OUT_Y_H_XL | LIS3DHH_REGISTER_READ, LIS3DHH_OUT_X_L_XL | LIS3DHH_REGISTER_READ);
    threeAxis->y = this->fromLSB2mg(threeAxis->yda);
    threeAxis->zda = this->readAxisReg(LIS3DHH_OUT_Z_H_XL | LIS3DHH_REGISTER_READ, LIS3DHH_OUT_Z_L_XL | LIS3DHH_REGISTER_READ);
    threeAxis->z = this->fromLSB2mg(threeAxis->xda);
}