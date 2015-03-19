/* 
 * File:   Serial.cpp
 * Author: Alex
 * 
 * Created on 17 марта 2015 г., 10:14
 */

#include "Serial.h"

Serial::Serial() {
}

Serial::Serial(const Serial& orig) {
}

Serial::~Serial() {
}

uint8_t Serial::uartInit()
{
    //open port
    UART = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    memset(&tty, 0, sizeof(tty));//put 0
    
    /*Error Handling*/
    if(tcgetattr(UART, &tty) != 0)
      {
        std::cout << "Error " << errno << " from tcgetattr: " << strerror(errno) << std::endl;
        return 1;
      }
    
    //set baudrate to 9600 bps
    cfsetospeed(&tty, (speed_t)B9600);
    
    //set port configuration no parity
    tty.c_cflag &= ~PARENB;//none parity bit
    tty.c_cflag &= ~CSTOPB;//none stop bit
    tty.c_cflag &= ~CSIZE;
    tty.c_cflag |= CS8;
    
    //diasble flow conrol
    tty.c_cflag &= ~CRTSCTS;
    
    tty.c_cc[VMIN] = 1;  //read doesn't block
    tty.c_cc[VTIME] = 5;//0.5 second read timeout
    
    tty.c_cflag |= CREAD | CLOCAL;  //turn on READ and set local mode
    
    /*Make raw*/
    cfmakeraw(&tty);//disable echo, special charectres etc.
    
    /*flush port and set attr*/
    tcflush(UART, TCIFLUSH);
    if(tcsetattr(UART, TCSANOW, &tty) != 0)
       {
        std::cout << "Error " << errno << " from tcsetattr" << std::endl;
        return 1;
       }
    
    return 0;
}

uint8_t Serial::uartRead(char *buffer)
{
  
}

uint8_t Serial::uartWrite(char *buffer)
{
    unsigned char cmd[] = "INIT \r";
    int n_written = 0;
    int spot = 0;
    
    /**/
    do{
        n_written = write(UART, &cmd[spot], 1);
        spot += n_written;
    } while(cmd[spot-1] != '\r' && n_written >0);
  return 0;  
}

