#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "chat.h"

void client_handler(int sockfd); // declare client_handler function


int main(int argc, char *argv[]){

	struct sockaddr_in addr;
	int sockfd;
	char *endptr;
	int port;

	// process optional argument for port
	if(argc>1)
		port = strtol(argv[1], &endptr, 10);
	else
		port = 9999;
		
	printf("[*] binding on localhost:%d\n", port);

 	// fill sockaddr_in structure
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htons(INADDR_ANY);

	// create the server socket
 	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(0);
	}

	// bind to the port defined 
	if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		perror("bind");
		exit(0);
	}

	// listen wiht one client at a time
	listen(sockfd,1);


	while(1){
		// loop over the client_handler method
		client_handler(sockfd);
	}


}

void client_handler(int sockfd){
	int new_sfd;
	struct sockaddr client_addr;
	char client_buff[INET_ADDRSTRLEN];
	
	//get size of client_addr
	socklen_t client_size = sizeof(&client_addr); 
	//accept connections
	new_sfd  = accept(sockfd, (struct sockaddr *) &client_addr, 
					&client_size);
	if(new_sfd == -1){
		perror("accept");
		exit(0);
	}
	
	//cast the sockaddr as a sockaddr_in in order to be able to get it's ip
	struct sockaddr_in *client_addr_in  = (struct sockaddr_in *) &client_addr;

	// get the ip of th econnected client
	inet_ntop(AF_INET, &(client_addr_in->sin_addr),
 		   	client_buff, INET_ADDRSTRLEN);

	printf("[*] new connection from %s\n", client_buff);
	printf("[*] starting chat\n");
	// start the chat which is defined in chat.h
	chat(new_sfd);
	printf("[*] connection closed\n");
	// once chat returns return to the loop in main in order to accept another connection
	return;
}

