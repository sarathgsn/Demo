

#include "application_header.h"

int main(int argc , char **argv )
{
    if(argc != 2 ) 
        handle_error("<use> <executble> </dev/devicename>") ; 

    int pid ; 
    int fd ; 
    char i ; 
    char buf ;  

    if ((fd = open(argv[1] , O_RDWR ))<0)
        handle_error("open"); ; 

    printf ("Open successful\n");
    pid = getpid() ; 
    printf ("Pid :%d\n" , pid);

    for(i=1 ; i<32 ; i++) { 
    read(fd ,&buf , sizeof(buf)) ;
    sleep(1) ; 
    printf ("reading from kerne_buf:%d\n" , buf);
    } 

    printf ("reading_done\n");

    return 0; 
}
