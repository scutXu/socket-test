#include "common.h"

#define SERV_PORT 9877



int main()
{
	int sockfd = Socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in servAddr;
	set_sock_addr(&servAddr,AF_INET,SERV_PORT,INADDR_LOOPBACK);
	Connect(sockfd,(const sockaddr *)(&servAddr),sizeof(servAddr));


	int a;
	cin>>a;
	cout<<"start close client sock"<<endl;
	close(sockfd);
	cout<<"finish close client sock<"<<endl;
}
