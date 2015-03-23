/* 
 * File:   Telemetry.h
 * Author: Alex
 *
 * Created on 20 марта 2015 г., 11:14
 */

#ifndef TELEMETRY_H
#define	TELEMETRY_H

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <mutex>
#include <netinet/in.h>

using namespace std;

class Telemetry {
public:
    Telemetry();
    Telemetry(const Telemetry& orig);
    virtual ~Telemetry();
    
    void setTelemetry(int *dataArr);
private:
    // RL -  rigth/left
    // FB - forward/back
    static int telRL, telFB;
    mutex tel_MUTEX;

};

#endif	/* TELEMETRY_H */

