

#include "application_header.h"

int main(int argc , char **argv )
{
    if(argc != 2 ) 
        handle_error("<use> <executble> </dev/devicename>") ; 

    int pid ; 
    int fd ; 
    char i ;  

    if ((fd = open(argv[1] , O_RDWR ))<0)
        handle_error("open"); ; 

    printf ("Open successful\n");
    pid = getpid() ; 
    printf ("Pid :%d\n" , pid);

    for(i=1 ; i < 32 ; i++) {
    write(fd ,&i , sizeof(i)) ;
    sleep(1) ; 
    printf ("Writing into kernel_buffer %d\n" , i);
    }

    printf ("Writing Done\n");

    return 0; 
}
