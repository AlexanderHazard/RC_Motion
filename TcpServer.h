/* 
 * File:   TcpServer.h
 * Author: Alex
 *
 * Created on 19 марта 2015 г., 10:57
 */

#ifndef TCPSERVER_H
#define	TCPSERVER_H

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <stdint.h>
#include <netdb.h>

#include "Telemetry.h"
#include "IMU_reader.h"
class TcpServer {
public:
    TcpServer();
    TcpServer(const TcpServer& orig);
    virtual ~TcpServer();
    
    uint8_t create(int port);
    
    struct sockaddr_in serv_addr;
    struct sockaddr_in local_addr;
    socklen_t local_addr_len=0;
private:
    int err, len, listen_desc, accept_desc;
    bool server_run = false;
    bool has_any_connect = false;
    ssize_t bytes_rec=0;
    int buffer[20];
    //int inBuf[12];
    
    Telemetry *telData;
    IMU_reader *imuData;

};

#endif	/* TCPSERVER_H */

