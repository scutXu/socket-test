//============================================================================
// Name        : get_local_ip.cpp
// Author      : xxl
// Version     :
// Copyright   : Your copyright notice
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
	int numIfreqRequested = 10;
	int numIfreqGetted = 0;
	do {
		reqs = new ifreq[numIfreqRequested];
		conf.ifc_ifcu.ifcu_req = reqs;
		conf.ifc_len = sizeof(ifreq) * numIfreqRequested;
		if(ioctl(sockfd,SIOCGIFCONF,&conf) < 0) {
			if(errno != EINVAL) {
				perror("ioctl");
				delete [] reqs;
				return -1;
			}
		}
		numIfreqGetted = conf.ifc_len / sizeof(ifreq);
		if(numIfreqGetted < numIfreqRequested && errno != EINVAL) {
			cout<<numIfreqGetted<<" ifreq getted."<<endl;
			break;
		}
		else {
			delete [] reqs;
			numIfreqRequested += IF_REQ_INCREMENT;
			cout<<"ifreq buffer is too small,increased to "<<numIfreqRequested<<endl;
		}

	} while(true);

	sockaddr_in * ipv4Address;
	for(int i=0;i<numIfreqGetted;++i) {
		ifreq & currentReq(reqs[i]);
		ipv4Address = (sockaddr_in *)(&currentReq.ifr_ifru.ifru_addr);
		cout<<currentReq.ifr_ifrn.ifrn_name<<':'<<inet_ntoa(ipv4Address->sin_addr)<<endl;
	}

	delete [] reqs;
	return 0;
}
