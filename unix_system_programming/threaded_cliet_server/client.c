#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

void chat(int sfd, char* name);
int chat_recv(int partner_sfd);
int chat_send(char* name, int partner_sfd);


int main(int argc, char* argv[]){
	
	struct sockaddr_in addr;
	int sockfd;
	char *ip, *endptr, *name;
	int port;
	
	// process the arguments
	//
	if(argc == 1){
		printf("USAGE %s <username> <ip(default localhost)> <port(default 9999)>\n", argv[0]);
		exit(1);
	}
	
	name = argv[1];
	
	if(argc >2)
		ip = argv[2];
	else
		ip = "127.0.0.1";
	if(argc > 3)
		port = strtol(argv[3], &endptr, 10);
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

	if(write(sockfd, "User ", 5) <=1){
		perror("write");
		exit(1);
	}

	if(write(sockfd,name  , strlen(name)) <=1){
		perror("write");
		exit(1);
	}

	if(write(sockfd," has joined" , 11) <=1){
		perror("write");
		exit(1);
	}

	chat(sockfd, name);
	
	
}

// this function recives characters from the given socket one at a time
// 	and prints them out until EOF or a new line
// 	returns the number of chars received
int chat_recv(int partner_sfd){
	int count = 0;
	int status;
	char c;
	
	while((status = read(partner_sfd, &c,  1)) != 0){
		if(status == -1){
			printf("recv failed");
			exit(0);
		}
		count++;
		printf("%c", c);
		if(c == '\n')
			break;
	}	
	return count;
}

// this function sends the name given and then gets characters
// 	one at a time form stdin and sends them to the given socket
// 	it stopps when it reaches a new line or or EOF
// 	returns the number of chars sent
int chat_send(char* name, int partner_sfd){
	char c;
	int count = 0;

	if(write(partner_sfd, name, strlen(name) +1 ) == -1){
		perror("send failed");
		exit(0);
	}
	if(write(partner_sfd, ": ", 2) == -1){
		perror("send failed");
		exit(0);
	}

	while((c = fgetc(stdin)) != 0){
		if(write(partner_sfd, &c, 1) == -1){
			perror("send failed");
			exit(0);
		}
		count++;
		if(c == '\n')
			break;
	}
	return count;
}

void chat(int partner_sfd, char* name){
	int sel;
	fd_set read_fds, test_fds;


	//nero out the fds
	FD_ZERO(&read_fds);
	// set the given partner fd and stdin 
	FD_SET(partner_sfd, &read_fds);
	FD_SET(0, &read_fds);

	while(1){
		// set the testfd's to the zeroed readfd's
		test_fds = read_fds;	
		// sellect over the fds
		sel = select(partner_sfd+1, &test_fds, NULL, NULL, NULL);
		if(sel == -1)
			perror("select");

		// if the socket is ready to be read call chat_recv
		if(FD_ISSET(partner_sfd, &test_fds)){
			if(chat_recv(partner_sfd) == 0  ){
				// if chat_recv returns 0 (socket is terminated) return
				close(partner_sfd);
				return;
			}
		}
		// if stdin is ready to be read call chat_send
		if(FD_ISSET(0, &test_fds)){
			if(chat_send(name, partner_sfd) == 0){
				// if chat_send returns 0 (socket is terminated) return
				close(partner_sfd);
				return;
			}
		}
	}
}
