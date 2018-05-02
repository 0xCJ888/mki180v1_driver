#include "mbed.h"
#include "mki180.hpp"

int main()
{
    mki180 accelMeasure;
    ThreeAxis dataMeasure;
    
    printf("whoami:%u \r\n", accelMeasure.getwhoami());
    accelMeasure.setCTRL_REG1(LIS3DHH_CTRL_REG1, LIS3DHH_CTRL_REG1_NORM_MOD_EN | LIS3DHH_CTRL_REG1_IF_ADD_INC);
    while(1){
        accelMeasure.get3axisdata(&dataMeasure);
        printf("x: %.4f\r\ny: %.4f\r\nz: %.4f\r\n", dataMeasure.x, dataMeasure.y, dataMeasure.z); 
        wait(1);
    }
    
}
