/* 
 * File:   TcpServer.cpp
 * Author: Alex
 * 
 * Created on 19 марта 2015 г., 10:57
 */

#include "TcpServer.h"

TcpServer::TcpServer() {
    telData = new Telemetry();
    imuData = new IMU_reader();
}

TcpServer::TcpServer(const TcpServer& orig) {
}

TcpServer::~TcpServer() {
}

uint8_t TcpServer::create(int port)
{
    int so_reuseaddr = 1;//if need set 1 else 0
    //AF_INET - IP socket
    //SOCK_STREAM - permanent connection socket
    //IPPROTO_TCP - tcp protocol using
    listen_desc = socket(AF_INET, SOCK_STREAM, 0);
        
    if(listen_desc < 0) 
      {
        perror("Can't create socket\n");
        return 1;
      }
    
        //set option SO_REUSEADDR
    //for reuse local address for bind
    setsockopt(listen_desc, SOL_SOCKET,  SO_REUSEADDR,  &so_reuseaddr, sizeof(so_reuseaddr));
   /* timeval tv;
    tv.tv_sec = 3000;
    tv.tv_usec = 0;
    setsockopt(listen_desc, SOL_SOCKET, SO_RCVTIMEO, (struct timeval *)&tv,sizeof(struct timeval));
  */  
    //Initialize server address struct to 0 
    bzero((char*)&serv_addr, sizeof(serv_addr));
    
    //set address which will be listening
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    
    //connect address struct to listen socket
    if((err = bind(listen_desc, (struct sockaddr*) &serv_addr, sizeof(struct sockaddr_in))) < 0)
      {
        close(listen_desc);
        //perror("Bind error!\n%s", gai_strerror(err));
        perror("Bind error!\n");
        return 2;
      }
     printf("Port %d was opened!\n", port);
             
    //try listen a socket
    if(listen(listen_desc, 0) < 0)
     {
        close(listen_desc);
        perror("listen error!\n");
        return 3;
     }
    
    server_run = true;//flag of client connection
    
    while(server_run)
     {
        /*check if client was connected*/
        if(!has_any_connect) 
          {
             //wait for connection from client
            if((accept_desc = accept(listen_desc, (struct sockaddr*) &local_addr, &local_addr_len)) < 0)
             {
              close(listen_desc);
              perror("Accept error!\n");
              return 4;
             }
            
          has_any_connect = true;
          }
        
        if((bytes_rec = recv(accept_desc, buffer, 8, 0)) <= 0)
          {
            perror("Client missed!\n");
            has_any_connect = false;
          }
        else 
        {
          telData->setTelemetry(buffer);//send to telemetry part 
          
          imuData->getDataIMU(buffer);
          usleep(5000);
          send(accept_desc, buffer, 12, 0);
          printf("%d\n",buffer[0]);
        }
               
     }
}