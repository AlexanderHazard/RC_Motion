/* 
 * File:   Telemetry.h
 * Author: Alex
 *
 * Created on 20 ����� 2015 �., 11:14
 */

#ifndef TELEMETRY_H
#define	TELEMETRY_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <mutex>
#include <netinet/in.h>
#include "PWM_process.h"

using namespace std;

class Telemetry : public PWM_process
{
public:
    Telemetry();
    Telemetry(const Telemetry& orig);
    virtual ~Telemetry();
    
    void setTelemetry(int *dataArr);
     void checkDataUpdate();//check if new data came
  
private:
    // RL -  rigth/left
    // FB - forward/back
    static int telRL, telFB;
    mutex tel_MUTEX;
    
    float PWM_QUIET = 0.09f;//percent of pwm, in which telemetry still
    float PWM_RL= 0;//percent of right or left pwm value
    float PWM_RL_STEPS = 15000.0f;//steps of RL_PWM shift
    int WHEEL_DIADE_ZONE = 50;//diade zones defines
    int L_MIN = -500, R_MAX = 500;//maximum values of right/left
    
    float PWM_FB_STEPS = 55555.0f;//steps of pwm shift
    float PWM_FB = 0;//percent of forward or back pwm value
    float FB_MAX = 500;//max value of forward back
    
    static bool update_flag;//flag state true when data new came,
   
};

#endif	/* TELEMETRY_H */

