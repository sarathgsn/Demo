
/* TCP  client program */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define MAX 100

int main(void)

{

    int sock_fd ;
    struct sockaddr_in v_clnt ;
    int len ;
    int ret_value ;
    char *ptr ;
    char buf[MAX] ;

    sock_fd = socket ( AF_INET, SOCK_STREAM, 0 ) ;

    if ( (-1) == sock_fd ) {
        perror ("socket") ;
        return -1 ;
    }

    v_clnt.sin_family = AF_INET ;
    v_clnt.sin_port = htons (4000) ;
    v_clnt.sin_addr.s_addr = inet_addr ("127.0.0.1");

    len = sizeof(v_clnt) ;

    ret_value = connect ( sock_fd, (const struct sockaddr *)&v_clnt, (socklen_t)len ) ;


    printf ("client : Connection established \n") ;

    while (1) {

        ptr = fgets ( buf, sizeof (buf), stdin ) ;

        if ( NULL == ptr ) {
            perror ("fgets") ;
            return -1 ;
        }

        ret_value = write ( sock_fd, buf, sizeof (buf) ) ;

       if ( (-1) == ret_value ) {
            perror ("write") ;
            return -1 ;
        }
        ret_value = read ( sock_fd, buf, sizeof (buf) ) ;

        if ( (-1) == ret_value ) {
            perror ("read") ;
            return -1 ;
        }

        printf ("client : %s \n", buf) ;

    }

    close ( sock_fd ) ;

    return 0 ;
}
