#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
#define MAXLINE 80

char** tok_line(char* line);
int exec_standard(char* command, char** args);
int exec_redirect(char** left, char** right);
int is_redirect(char** command);


int main() {
char * prompt;
// First check for the PS1 envrionment variable, if its not there use default prompt
if((prompt = getenv("PS1")) == NULL)
   prompt = "shell> ";

// Loop forever over the shell 
    while(1){
        char line[MAXLINE+1];
        char** command;
		int i = 0;
		// Print the primpt
        printf("%s ",prompt);
		// Get the line of input
		fgets(line,MAXLINE,stdin);
		// remove the trailing new line and set it to 0
        line[strcspn(line,"\n")] = 0;
		// call my tokenize line function
        command = tok_line(line);
		int position = 0; 
		// check if the line contains a < or >
		if((position = is_redirect(command)) != -1){
			//execute a redirect by passing in the initial command and the 
			// 	position of the < or > 
			exec_redirect(command, command + position);
			while( command[i]){
				free(command[i]);
				i++;
			}
			free(command);
		}
		else if(strcmp(command[0], "exit") == 0){
			break;
		}
		// Implement cd
		else if(command[1] && strcmp(command[0], "cd") == 0) {
			// I am using environment variables to keep track of the directory
			// get the pwd
			char * pwd = getenv("PWD");
			// set the size of the new pwd
			int buf_size = strlen(pwd) + MAXLINE + 2;
			char path[buf_size];
			// if the user gave .. chdir to .. and remove the last folder form the current pwd
			if(strcmp(command[1], "..") == 0){
				if(chdir("..") != -1){
					// this sets the contents of the poster to the last occurance if / to null
					*(strrchr(pwd, '/')) = '\0';
					setenv("PWD", path, 1);
				}
			}
			else{
				// copy the pwd plus the new folder
				strcat(path, pwd);
				strcat(path, "/");
				strcat(path, command[1]);
				if(chdir(path) != -1)
					setenv("PWD", path, 1);
			}
		}
		// if the line has a length attempt ot execute a standard command
		else if(strlen(line) > 0) {
			// execute a standard command
			exec_standard(command[0], command);
			while( command[i]){
				free(command[i]);
				i++;
			}
			free(command);
		}

    }
}

char** tok_line(char* line) {
	// Allocate a char ** with a maximum of MAXLINE/2+1 strings 
	// 	(at most there will be MAXLINE/2 1 char space seperated strings)
	char ** command_arr = (char**)malloc(sizeof(char*)* (MAXLINE/2 + 1));
	if(command_arr == NULL){
		perror("error in malloc\n");
		exit(1);
	}
	// Allocate a char* with a max size of MAXLINE
	// 	(the longest string will be one string that is MAXLINE chars long
    for(int i =0; i< MAXLINE/2 +1 ; i++){
		command_arr[i] = (char*)malloc(sizeof(char) * MAXLINE);
        if(command_arr[i] == NULL){
			perror("error in malloc\n");
			exit(1);
		}
    }

	// begin to tokenize the line on spaces
    char* tok = strtok(line, " ");
    int i = 0;
    while(tok) {
		// copy the strings into the allocated array
        strcpy(command_arr[i], tok);
        tok = strtok(NULL, " ");
        i++;
    }
	//	end the array with a null char
    command_arr[i] = '\0';

	// return the array 
    return command_arr;
}

// This function executes a standard command 
int exec_standard(char* command, char** args) {

	if(fork() == 0){
		// exec the command in the child
		if( execv(command, args) == -1){
			return -1;
		}
		exit(1);
	}	
	else{
		// wait in the parent
		wait(NULL);
	}
	return 0;
}

// This function executes a file redirection command
int exec_redirect(char** left, char** right) {
	// attempt to open the file which is on the right side of the command
	int file = open(right[1], O_RDWR | O_CREAT, 0666);
	if(file == -1) {
		perror("errer opening file");
		exit(-1);
	}
	// switch on the position of the redirect
	// set the redirect to null so exec doesnt read past it
	if(fork() == 0) {
 		switch (right[0][0]){
			case '<':
				// if the redirect is < duplicate STDIN  to the file
				if(dup2(file, STDIN_FILENO) == -1){
					perror("error in dup2\n");
					exit(1);
				}
				break;
			case '>':
				// if the redirect is < duplicate STDOUT  to the file
				if(dup2(file, STDOUT_FILENO) == -1){
					perror("error in dup2\n");
					exit(1);
				}
				break;
		}

		right[0] = '\0';
		if( execv(left[0], left) == -1){
			close(file);
			return -1;
		}
		exit(1)
	}
	else
		wait(NULL);
	// close the file and return
	close(file);
	return 0;
}

// This funtion checks for a redirect char and if found, returns its index
int is_redirect(char** command){
	int i = 0;
	while(command[i]){
		if(strchr(command[i], '<')  || strchr(command[i], '>'))
			return i;
		i++;
	}
	return -1;
}
