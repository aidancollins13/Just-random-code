#include "types.h"
#include "user.h"

//Function that reads one char at a times and stops at new line
//    then puts line into given buffer.
//    returns the length of string read.

int readLine(const int fd, char *buff, int bufsize){
    char ch[1];
    int s = 0;
    while(read(fd, ch, 1) > 0){
        if(s > bufsize){
                printf(2, "Error: line in readLine to large for given buffer\n"); //Added to avoid using funciton for buffer overflows.
                exit();
        }
        buff[s++] = *ch;
        if(*ch == '\n'){
            return s;
        }
    }
    return 0;
}

int main(int argc,char *argv[]) {
    int  fd = 0;                //File Discriptor. Defaults to stdin.
    int  n = 10;                //Lines. Defaults to 10.
    char buff[512];

    if(argc == 2){              //If the program has one argemnt.  Then checks weather that is a -NUM or FILE
        if(*argv[1] == '-')
            n = atoi((argv[1] + 1));
        else if((fd = open(argv[1], 0)) < 0){
            printf(2,"%s: Error: Cannot open %s\n",argv[0], argv[1]);
            exit();
        }
    }

    if(argc == 3) {             //If the program has 2 or more arguments assumes it is in the format -NUM FILE
        if((fd = open(argv[2], 0)) < 0){  //  Does not accept more than one file
            printf(2,"%s: Error: Cannot open %s\n",argv[0], argv[2]);
            exit();
        }
        n = atoi((argv[1] +1 ));
        printf(1, "%s", argv[2]);
    }
    for(int i = 0; i < n; i ++){ //This prints the appropriate number of lines
        write(1, buff, readLine(fd, buff, sizeof(buff)));
    }

    close(fd);
    exit();
}
