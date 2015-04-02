/* 
 * File:   Telemetry.cpp
 * Author: Alex
 * 
 * Created on 20 марта 2015 г., 11:14
 */

#include "Telemetry.h"

int Telemetry::telFB;
int Telemetry::telRL;

Telemetry::Telemetry() {
}

Telemetry::Telemetry(const Telemetry& orig) {
}

Telemetry::~Telemetry() {
}

void Telemetry::setTelemetry(int* dataArr)
{
  tel_MUTEX.lock();
   if((telFB != ntohl(dataArr[1])))  
   {
       telFB = ntohl(dataArr[1]);
       //telRL = ntohl(dataArr[1]);
       //setPWM(1, 0.5);//write pwm value in class PWM_process
   }
  
  if (telRL != ntohl(dataArr[0])) 
   {
      telRL = ntohl(dataArr[0]);
      
      //if wheel in deade zone 
      if((telRL > WHEEL_DIADE_ZONE) && (telRL < (-1*WHEEL_DIADE_ZONE))) PWM_RL = 0;
        else
          {
          //else calculate pwm value
          /*
           * we substract diade zone from rotation value
           * and then divide by number of steps
           *so we get percent value of rotation pwm
           */ 
          if(telRL < 0)//if wheel rotate to left
              {
               PWM_RL = (telRL + WHEEL_DIADE_ZONE)/PWM_RL_STEPS;
              }
          else if(telRL > 0)//if wheel rotate to right
              {
               PWM_RL = (telRL - WHEEL_DIADE_ZONE)/PWM_RL_STEPS;
              }
           }
      printf("PWM_RL = %f!\n", PWM_RL);
      PWM_RL = PWM_QUIET + PWM_RL;
   }
 tel_MUTEX.unlock();    
    printf("FB = %d, RL = %d, PWM_RL = %f!\n", telFB, telRL, PWM_RL);
}
