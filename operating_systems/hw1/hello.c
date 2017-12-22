#include "types.h"
#include "user.h"

int main(){
    write(1, "Hello World!\n", 13);  //Uses write to stdout(1) because other print functions (printf()) are not defined in xv6
    exit();
}
