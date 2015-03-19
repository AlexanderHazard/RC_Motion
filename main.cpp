/* 
 * File:   main.cpp
 * Author: Alex
 *
 * Created on 16 марта 2015 г., 9:29
 */

#include <cstdlib>

#include "IMU_reader.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv) {

    IMU_reader imu;
    imu.read_cycle();
    return 0;
}

