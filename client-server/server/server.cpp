#include "common.h"

#define SERV_PORT 9877
#define LISTENQ 1

int main() {
	int listenfd = Socket(AF_INET,SOCK_STREAM,0);

	sockaddr_in servAddr;
	sockaddr_in cliAddr;

	set_sock_addr(&servAddr,AF_INET,SERV_PORT,INADDR_ANY);
	
	Bind(listenfd,(const sockaddr *)(&servAddr),sizeof(servAddr));

	Listen(listenfd,LISTENQ);

	size_t cliAddrSize = sizeof(cliAddr);
	int connfd = Accept(listenfd,(sockaddr *)(&cliAddr),&cliAddrSize);

	int a;
	cin>>a;
	cout<<"start close conn sock"<<endl;
	close(connfd);
	cout<<"finish close conn sock"<<endl;

	cin>>a;
	cout<<"start close listen sock"<<endl;
	close(listenfd);
	cout<<"finish close listen sock"<<endl;
	
	return 0;
}
