/* 
 * File:   main.cpp
 * Author: Alex
 *
 * Created on 16 марта 2015 г., 9:29
 */

#include <cstdlib>
#include <thread>

#include "IMU_reader.h"
#include "TcpServer.h"
#include "PWM_process.h"
#include "Telemetry.h"

using namespace std;

/*
 * 
 */

void thread_tcp()
{
    TcpServer tcp;
    tcp.create(5555);
}

void thread_imu(void)
{
    IMU_reader imu;
    imu.read_cycle();
}

void thread_telemetry_watch(void)
{
    Telemetry tel_watch;
    tel_watch.checkDataUpdate();
}

int main(int argc, char** argv) {
    
   /* PWM_process *pwm = new PWM_process();
    float duty = 0.0f;
    bool r = true;
    
    while(1)
    {
      if(duty >= 0.9f) r = false;
      else if(duty <= 0.1f) r = true;
        
      if((duty < 1.0f) && r)  {duty += 0.01f; pwm->setPWM(1, duty);}
      else if((duty > 0.0f) && !r)  {duty -= 0.01f; pwm->setPWM(1, duty);}
      usleep(3000);
      
    }*/
    //thread imuThread;
    
    //IMU_reader imu;
    //TcpServer tcp;
    //tcp.create(5555);
    
    //thread imuThread(&IMU_reader::read_cycle, IMU_reader());//Thread which read imu from sensors
    thread imuThread(thread_imu);
    thread tcpThread(thread_tcp);
    thread telThread(thread_telemetry_watch);
    
    imuThread.join();
    tcpThread.join();
    telThread.join();
    //imu.read_cycle();
    return 0;
}

