#include "mbed.h"
#include "mki180.hpp"

int main()
{
    mki180 accelMeasure;
    ThreeAxis dataMeasure;
    
    printf("whoami:%u \r\n", accelMeasure.getwhoami());
    while(1){
        accelMeasure.get3axisdata(&dataMeasure);
        printf("x: %f\r\ny: %f\r\nz:%f\r\n", dataMeasure.x, dataMeasure.y, dataMeasure.z); 
        wait(1);
    }
    
}
