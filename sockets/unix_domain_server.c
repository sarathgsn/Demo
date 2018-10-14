
/* TCP server program */
#include<string.h>
#include <sys/un.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#define name "sarath"
#define MAX 100

int main(void)

{  
    struct sockaddr_un client, server;
    int sock_fd ;
   
    int fd ;
    int ret_value ;
    char *ptr ;
    char buf[MAX] ;

     sock_fd = socket ( AF_UNIX, SOCK_STREAM, 0 ) ;

   if ( (-1) == sock_fd ) {
        perror ("socket") ;
        return -1 ;
    }

     client.sun_family = AF_UNIX;
     strcpy(client.sun_path , name);
 

    ret_value = bind ( sock_fd, (const struct sockaddr *)&client, SUN_LEN(&client)) ;

    if ( (-1) == ret_value ) {
        perror ("bind") ;
        return -1 ;
    }

    ret_value = listen (sock_fd, 5) ;

    if ( (-1) == ret_value ) {
        perror ("listen") ;
        return -1 ;
    }

    printf ("server : Waiting for connections \n") ;

    fd = accept ( sock_fd, NULL, NULL ) ;

   if ( (-1) == fd ) {
        perror ("accept") ;
        return -1 ;
    }

    printf ("server : Connection established \n") ;
    unlink(name);
    while (1) {
    
        ret_value = read ( fd, buf, sizeof (buf) ) ;

        if ( (-1) == ret_value ) {
            perror ("read") ;
            return -1 ;
        }

        printf ("client : %s \n", buf) ;

        ptr = fgets ( buf, sizeof (buf), stdin ) ;

        if ( NULL == ptr ) {
            perror ("fgets") ;
             return -1 ;
        }
 
        ret_value = write ( fd, buf, sizeof (buf) ) ;

        if ( (-1) == ret_value ) {
            perror ("write") ;
            return -1 ;
        }

    }
    close ( sock_fd ) ;
        
    return 0 ;
}
