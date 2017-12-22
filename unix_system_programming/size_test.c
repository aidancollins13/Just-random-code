#include<stdlib.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>

int main(int argc, char** argv){

struct stat sb;
if((lstat(argv[1], &sb)) == -1){
    perror("error on stat()");
    exit(0);
}

printf("size of test dir %d\n", (sb.st_blocks * 512)/1024);


}
