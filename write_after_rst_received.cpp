//============================================================================
// Name        : write_after_rst_received.cpp
// Author      : xxl
// Version     :
// Copyright   :
// Description :
//============================================================================

#include <iostream>
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

#define NONE_LISTENED_PORT 3000

void signalHandler(int signalType)
{
	cout<<"handle signal:"<<signalType<<endl;
}

int main() {
	signal(SIGPIPE,signalHandler);

	int sockfd;
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("socket");
		return -1;
	}

	sockaddr_in serverAddress;
	memset(&serverAddress,0,sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_port = htons(NONE_LISTENED_PORT);		//没有套接字在监听的端口
	serverAddress.sin_addr.s_addr = htonl(INADDR_LOOPBACK);	//环路地址，用于模拟服务器

	if(connect(sockfd,(sockaddr *)(&serverAddress),sizeof(serverAddress)) < 0) {
		perror("connect");
	}
	char message[12] = "Hello Wrold";
	write(sockfd,message,sizeof(message));

	close(sockfd);
	cout<<"exit"<<endl;
}
