#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {

    uint salt[4];
    u_char * f_salt;
    for (int i = 0; i< 4; i++){
        salt[i] = rand();
    }
    printf("%d\n", rand());

    f_salt = (u_char*)salt;
    for (int  i = 0; i<16; i++)
        printf("%x", f_salt[i]);


}
