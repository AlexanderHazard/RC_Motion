/* 
 * File:   PWM_process.h
 * Author: Alex
 *
 * Created on 23 марта 2015 г., 14:30
 */

#ifndef PWM_PROCESS_H
#define	PWM_PROCESS_H
#include <stdint.h>
#include <stdio.h>

using namespace std;

class PWM_process {
public:
    PWM_process();
    PWM_process(const PWM_process& orig);
    virtual ~PWM_process();
    
    uint8_t startPWM();
    void setPWM(int channel, float duty);
private:
    
     FILE *fp;

};

#endif	/* PWM_PROCESS_H */

