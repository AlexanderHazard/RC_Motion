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
    
    telFB = ntohl(dataArr[0]);
    
    telRL = ntohl(dataArr[1]);
    
 tel_MUTEX.unlock();    
    printf("FB = %d, RL = %d!\n", telFB, telRL);
}
