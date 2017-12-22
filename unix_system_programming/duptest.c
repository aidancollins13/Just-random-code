
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc, char**argv){
	int file = open("file", O_RDWR | O_CREAT, 0666);
	dup2(file, 1);
	execl(argv[0], argv);
}
