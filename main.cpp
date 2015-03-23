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

int main(int argc, char** argv) {

    //thread imuThread;
    
    //IMU_reader imu;
    //TcpServer tcp;
    //tcp.create(5555);
    
    //thread imuThread(&IMU_reader::read_cycle, IMU_reader());//Thread which read imu from sensors
    thread imuThread(thread_imu);
    thread tcpThread(thread_tcp);
    
    imuThread.join();
    tcpThread.join();
    //imu.read_cycle();
    return 0;
}

