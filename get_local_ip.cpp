//============================================================================
// Name        : test.cpp
// Author      : xxl
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <stdio.h>
#include <sys/errno.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <netinet/in.h>

using namespace std;

#define IF_REQ_INCREMENT 10

int main() {
	int sockfd;
	if((sockfd = socket(AF_INET,SOCK_STREAM,0)) < 0) {
		perror("socket");
		return -1;
	}

	ifconf conf;
	ifreq * reqs;
	int numIfreq = 10;
	do {
		reqs = new ifreq[numIfreq];
		conf.ifc_ifcu.ifcu_req = reqs;
		conf.ifc_len = sizeof(ifreq) * numIfreq;
		if(ioctl(sockfd,SIOCGIFCONF,&conf) < 0) {
			if(errno != EINVAL) {
				perror("ioctl");
				delete [] reqs;
				return -1;
			}
		}
		if(conf.ifc_len < numIfreq && errno != EINVAL) {
			cout<<conf.ifc_len<<" ifreq getted."<<endl;
			break;
		}
		else {
			delete [] reqs;
			numIfreq += IF_REQ_INCREMENT;
			cout<<"ifreq buffer is too small,increased to "<<numIfreq<<endl;
		}

	} while(true);

	sockaddr_in * ipv4Address;
	for(int i=0;i<conf.ifc_len;++i) {
		ifreq & currentReq(reqs[i]);
		ipv4Address = (sockaddr_in *)(&currentReq.ifr_ifru.ifru_addr);
		cout<<currentReq.ifr_ifrn.ifrn_name<<':'<<inet_ntoa(ipv4Address->sin_addr)<<endl;
	}

	delete [] reqs;
	return 0;
}
