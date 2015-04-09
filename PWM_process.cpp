/* 
 * File:   PWM_process.cpp
 * Author: Alex
 * 
 * Created on 23 марта 2015 г., 14:30
 */

#include "PWM_process.h"

PWM_process::PWM_process() {
}

PWM_process::PWM_process(const PWM_process& orig) {
}

PWM_process::~PWM_process() {
}

uint8_t PWM_process::startPWM()
{
  
}

void PWM_process::setPWM(int channel, float duty)
{
    //try to open file
    fp = fopen("/dev/pi-blaster", "w");
    if(fp == NULL)
     {
        printf("Error opening file\n");
        return;
    }
    
    fprintf(fp, "%i=%f\n", channel, duty);
    fflush(fp);
    fclose(fp);
}
