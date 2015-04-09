/* 
 * File:   Telemetry.cpp
 * Author: Alex
 * 
 * Created on 20 марта 2015 г., 11:14
 */

#include "Telemetry.h"
#include <unistd.h>
//800 is random change number which more then 500
int Telemetry::telFB = 800;
int Telemetry::telRL = 800;
bool Telemetry::update_flag = false;

Telemetry::Telemetry() {
}

Telemetry::Telemetry(const Telemetry& orig) {
}

Telemetry::~Telemetry() {
}

void Telemetry::setTelemetry(int* dataArr)
{
  tel_MUTEX.lock();
  
  update_flag = true;//change flag of data update
  
   if((telFB != ntohl(dataArr[1])))  
   {
       telFB = ntohl(dataArr[1]);
       
       PWM_FB = (telFB/PWM_FB_STEPS) + PWM_QUIET;
       //PWM_FB = PWM_QUIET + PWM_FB;
         setPWM(4, PWM_FB);//write pwm value in class PWM_process
   }
  
  if (telRL != ntohl(dataArr[0])) 
   {
      telRL = ntohl(dataArr[0]);
      
      //if wheel in deade zone 
      if((telRL < WHEEL_DIADE_ZONE) && (telRL > (-1*WHEEL_DIADE_ZONE))) PWM_RL = 0;
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
      setPWM(5, PWM_RL);
   }
 tel_MUTEX.unlock();    
    printf("FB = %d, RL = %d, PWM_FB = %2.3f,  PWM_RL = %2.3f!\n", telFB, telRL, PWM_FB, PWM_RL);
}

void Telemetry::checkDataUpdate()
{
   while(1)
    {
     tel_MUTEX.lock();
      if(!update_flag) 
       {
        //if new data didn't update clear them
          setPWM(4, PWM_QUIET);
          setPWM(5, PWM_QUIET);
       }
      else 
          update_flag = false;//change flag of data update
    tel_MUTEX.unlock();
    sleep(1);//check every 1 seconds for data update
   }
}
