#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "chat.h"


int main(int argc, char* argv[]){
	
	struct sockaddr_in addr;
	int sockfd;
	char *ip, *endptr;
	int port;
	
	// process the arguments
	if(argc >1)
		ip = argv[1];
	else
		ip = "127.0.0.1";
	if(argc > 2)
		port = strtol(argv[2], &endptr, 10);
	else
		port = 9999;

	// fill the sockaddr_int struct
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);

 	if(inet_pton(AF_INET, ip, &addr.sin_addr) == -1){
		perror("invalid ip");
		exit(0);
	}	

	// create a socket
	if((sockfd = socket(AF_INET, SOCK_STREAM,0)) == -1){
		perror("socket");
		exit(0);
	}

	// connect the socket to the address given
	if(connect(sockfd, (struct sockaddr*) &addr, sizeof(addr)) == -1){
		perror("connect");
		exit(0);
	}
	printf("[*] starting chat\n");
	// call chat which is in chat.h
	chat(sockfd);
	
}
