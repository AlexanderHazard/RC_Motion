/* 
 * File:   Serial.h
 * Author: Alex
 *
 * Created on 17 марта 2015 г., 10:14
 */

#ifndef SERIAL_H
#define	SERIAL_H

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>//file control
#include <errno.h>
#include <termios.h>//terminal control
#include <stdint.h>


class Serial {
public:
    Serial();
    Serial(const Serial& orig);
    virtual ~Serial();
    
    uint8_t uartInit();
    uint8_t uartRead(char*);
    uint8_t uartWrite(char*);
private:
    struct termios tty;
    int UART;
    

};

#endif	/* SERIAL_H */

