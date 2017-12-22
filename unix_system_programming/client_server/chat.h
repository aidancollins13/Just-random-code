#include <sys/select.h>
#include <unistd.h>
#include <string.h>
// this function recives characters from the given socket one at a time
// 	and prints them out until EOF or a new line
// 	returns the number of chars received
int chat_recv(int partner_sfd){
	int count = 0;
	int status;
	char c;
	
	while((status = recv(partner_sfd, &c,  1, 0)) != 0){
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

	if(send(partner_sfd, name, strlen(name) +1 , 0) == -1){
		perror("send failed");
		exit(0);
	}
	if(send(partner_sfd, ": ", 3 , 0) == -1){
		perror("send failed");
		exit(0);
	}

	while((c = fgetc(stdin)) != 0){
		if(send(partner_sfd, &c, 1, 0) == -1){
			perror("send failed");
			exit(0);
		}
		count++;
		if(c == '\n')
			break;
	}
	return count;
}

void chat(int partner_sfd){
	int sel;
	char name[25];
	fd_set read_fds, test_fds;

	//prompt the user for a name and store it in name
	printf("[*] Please enter your name (max 25 letters): ");
	fgets(name, 25, stdin);
	// remove the trailing newline:
	name[strcspn(name, "\n")] =0;
	printf("[*] Hello %s!\n", name);

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
