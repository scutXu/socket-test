#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
using namespace std;

int Socket(int domain, int type, int protocol);
void set_sock_addr(sockaddr_in * addr,sa_family_t sin_family,uint16_t sin_port,const char * s_addr);
void set_sock_addr(sockaddr_in * addr,sa_family_t sin_family,uint16_t sin_port,uint32_t s_addr);
void Connect(int sockfd,const sockaddr * servAddr,size_t addrSize);
void Bind(int listenfd,const sockaddr * servAddr,size_t addrSize);
void Listen(int listenfd,int n);
int Accept(int listenfd,sockaddr * cliAddr,size_t * cliAddrSize);
ssize_t Read(int fd,void * buf,size_t nbytes);
ssize_t Write(int fd,const void * buf,size_t nbytes);
void loop(int sockfd);