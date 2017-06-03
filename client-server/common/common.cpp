#include "common.h"

#define READ_BUF 1024

int Socket(int domain, int type, int protocol)
{
	int sockfd;
	if((sockfd = socket(domain,type,protocol)) < 0) {
		perror("socket");
		exit(1);
	}
	return sockfd;
}

void set_sock_addr(sockaddr_in * addr,sa_family_t sin_family,uint16_t sin_port,const char * s_addr)
{
	memset(addr,0,sizeof(sockaddr_in));
	addr->sin_family = sin_family;
	addr->sin_port = htons(sin_port);
	if(inet_pton(sin_family,s_addr,&addr->sin_addr) != 1) {
		perror("inet_pton");
		exit(1);
	}
}

void set_sock_addr(sockaddr_in * addr,sa_family_t sin_family,uint16_t sin_port,uint32_t s_addr)
{
	memset(addr,0,sizeof(sockaddr_in));
	addr->sin_family = sin_family;
	addr->sin_port = htons(sin_port);
	addr->sin_addr.s_addr = htonl(s_addr);
}

void Connect(int sockfd,const sockaddr * servAddr,size_t addrSize)
{
	if(connect(sockfd,servAddr,addrSize) < 0) {
		perror("connect");
		exit(1);
	}
}

void Bind(int listenfd,const sockaddr * servAddr,size_t addrSize)
{
	if(bind(listenfd,servAddr,addrSize) < 0) {
		perror("bind");
		exit(1);
	}
}


void Listen(int listenfd,int n)
{
	if(listen(listenfd,n) < 0) {
		perror("listen");
		exit(1);
	}
}

int Accept(int listenfd,sockaddr * cliAddr,size_t * cliAddrSize)
{
	int connfd;
	if((connfd = accept(listenfd,cliAddr,cliAddrSize)) < 0) {
		perror("accept");
		exit(1);
	}
	return connfd;
}

ssize_t Read(int fd,void * buf,size_t nbytes)
{
	ssize_t n = read(fd,buf,nbytes);
	if(n < 0) {
		perror("read");
		exit(1);
	}
	return n;
}
ssize_t Write(int fd,const void * buf,size_t nbytes)
{
	ssize_t n = write(fd,buf,nbytes);
	if(n < 0) {
		perror("write");
		exit(1);
	}
	return n;
}

void loop(int sockfd)
{
	char order;
	char writeBuf[6] = "hello";
	char readBuf[READ_BUF];
	memset(readBuf,0,READ_BUF);

	while(true) {
		cin>>order;
		if(order == 'c') {
			close(sockfd);
			return;
		}

		switch(order) {
			case 'r':
			{
				ssize_t n = Read(sockfd,(void *)readBuf,READ_BUF);
				if(n == 0) {
					close(sockfd);
					return;
				}
				cout<<readBuf;
				memset(readBuf,0,READ_BUF);
				break;
			}
			case 'w':
			{
				Write(sockfd,(const void *)writeBuf,sizeof(writeBuf));
				break;
			}
			default:
				break;
		}
	}
}