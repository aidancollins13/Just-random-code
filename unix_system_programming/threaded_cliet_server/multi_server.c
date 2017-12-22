#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <strings.h>
#define BUFF_LENGTH 1024


struct client_info {
	int sockfd;
	struct client_info *next;
} ;

pthread_mutex_t message_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_mutex_t client_lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t writing_done_cond = PTHREAD_COND_INITIALIZER;
pthread_cond_t reading_done_cond = PTHREAD_COND_INITIALIZER;

char message_buffer[BUFF_LENGTH];
struct client_info* clients = NULL;

void * client_thread(void* sfd);
void * sender_thread();
void * listening_thread(void* sfd);
void add_client(int sfd);
void remove_client(int sfd);

int main(int argc, char* argv[]){

	struct sockaddr_in addr;
	int sockfd;
	char* endptr;
	int port;
	pthread_t listening, sender;

	pthread_mutex_init(&message_lock, NULL);
	pthread_mutex_init(&client_lock, NULL);
	pthread_cond_init(&writing_done_cond, NULL);
	pthread_cond_init(&reading_done_cond, NULL);

	if(argc > 1)
		port = strtol(argv[1], &endptr, 10);
	else
		port = 9999;

	printf("[*] binding on localhost:%d\n", port);

	// fill sockaddr_in structure
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = htons(INADDR_ANY);

	//create the server socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1){
		perror("socket");
		exit(0);
	}

	//bind to the port defined
	if(bind(sockfd, (struct sockaddr *) &addr, sizeof(addr)) == -1){
		perror("bind");
		exit(0);
	}
	
	//create a thread to listen
	printf("[*] createing listening thread\n");
	pthread_create(&listening, NULL, listening_thread, &sockfd);

	// create sender thread	
	printf("[*] createing sender thread\n");
	pthread_create(&sender, NULL, sender_thread, &sockfd);

	pthread_join(listening, NULL);

}


void* listening_thread(void* sfd){

	int new_sfd;
	struct sockaddr client_addr;
	char client_buff[INET_ADDRSTRLEN];
	pthread_t client;
	int sockfd = *((int*) sfd);

	listen(sockfd, 1);

	while(1){
		socklen_t client_size = sizeof(&client_addr);
		new_sfd = accept(sockfd, (struct sockaddr *) &client_addr,
				&client_size);
		if(new_sfd == -1){
			perror("accept");
			exit(0);
		}

		// cast the sockaddr as a sockaddr_in in order to get the ip
		struct sockaddr_in *client_addr_in = (struct sockaddr_in*) &client_addr;

		// get the ip of the connected client
		inet_ntop(AF_INET, &(client_addr_in->sin_addr),
				client_buff, INET_ADDRSTRLEN);

		printf("[*] new connection from %s\n", client_buff);
		
		// add the client to the global list
		add_client(new_sfd);

		// spin up a thread for the client
		printf("[*] creating new client thread\n");
		pthread_create(&client, NULL, client_thread,  &new_sfd);
	}
}

void* sender_thread(){
	char local_buff[BUFF_LENGTH];
	while(1){

		//get buf lock
		pthread_mutex_lock(&message_lock);
		// check if there is anything in the buffer and if not wait for the cond
		while(strlen(message_buffer) == 0)
			pthread_cond_wait(&writing_done_cond, &message_lock);

		printf("[*] message ready to be sent\n");

		strncpy(local_buff, message_buffer, BUFF_LENGTH);
		memset(message_buffer, 0, BUFF_LENGTH);
	
		//send the reading _done signal and unlock
		pthread_cond_signal(&reading_done_cond);
		pthread_mutex_unlock(&message_lock);

		//get client lock
		pthread_mutex_lock(&client_lock);
		struct client_info* c = clients;
		while(c != NULL){
			if(write(c->sockfd, local_buff, sizeof(local_buff)) == -1){
				perror("write");
				continue;
			}

			c = c->next;
		}
		// release client lock
		pthread_mutex_unlock(&client_lock);

	}

	
}

void* client_thread(void* fd){
	int client_sfd = *((int*)fd);

	while(1){

		//get message lock
		pthread_mutex_lock(&message_lock);
		while(strlen(message_buffer) != 0)
			pthread_cond_wait(&reading_done_cond, &message_lock);
		
		printf("[*] reading from client %d\n", client_sfd);

		if(read(client_sfd, message_buffer, BUFF_LENGTH) == 0){
			printf("[*] removing client\n");
			remove_client(client_sfd);
			pthread_cond_signal(&writing_done_cond);
			pthread_mutex_unlock(&message_lock);
			pthread_exit(NULL);
		}


		//send the signal and unlock
		pthread_cond_signal(&writing_done_cond);
		pthread_mutex_unlock(&message_lock);

	}

}

void add_client(int sfd){

	struct client_info * new_client;
	new_client = (struct client_info*) malloc(sizeof(struct client_info));

	if(new_client == NULL){
		perror("malloc");
		exit(0);
	}

	new_client->sockfd = sfd;
	new_client->next = NULL;

	printf("[*] adding new client %d\n", sfd);

	pthread_mutex_lock(&client_lock);

	struct client_info * c = clients;

	if(c == NULL){
		clients = new_client;
		pthread_mutex_unlock(&client_lock);
		return;
	}

	while(c->next != NULL)
		c = c->next;

	c->next =  new_client;

	pthread_mutex_unlock(&client_lock);
	return;
	
}
	
void remove_client(int sfd){

	struct client_info * c;

	pthread_mutex_lock(&client_lock);
	c = clients;
	if(c == NULL){
		pthread_mutex_unlock(&client_lock);
		return;
	}

	if(c->sockfd == sfd){
		clients = c->next;
		printf("[*] freeing client %d\n", c->sockfd);
		free(c);
	}
	while(c->next != NULL){
		if(c->next->sockfd == sfd){
			struct client_info * temp = c->next;
			c->next = c->next->next;
			printf("[*] freeing client %d\n", temp->sockfd);
			free(temp);
		}
		else
			c = c->next;
	}

	pthread_mutex_unlock(&client_lock);
	return;
}
