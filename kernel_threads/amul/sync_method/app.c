

#include "application_header.h"

int main(int argc , char **argv )
{
    if(argc != 2 ) 
        handle_error("<use> <executble> </dev/devicename>") ; 

    int pid ; 
    int fd ; 
    char buf[20] ; 
    char var = 'y' ; 

    if ((fd = open(argv[1] , O_RDWR ))<0)
        handle_error("open"); ; 

    printf ("Open successful\n");
    pid = getpid() ; 
    printf ("Pid :%d\n" , pid) ;

    read(fd, buf, 20) ;
    sleep(1) ; 
    write(fd ,&var, sizeof(var)) ; 

    if ((ioctl ( fd , pid , getppid() ))<0)
        handle_error("ioctl");

    getchar() ;

    return 0; 
}
