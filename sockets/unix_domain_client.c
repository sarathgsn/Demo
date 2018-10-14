
/* TCP  client program */
#include<sys/un.h>
#include<string.h>
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
    struct sockaddr_un client;
    int sock_fd ;
    int len ;
    int ret_value ;
    char *ptr ;
    char buf[MAX] ;

    sock_fd = socket ( AF_UNIX, SOCK_STREAM, 0 ) ;

    if ( (-1) == sock_fd ) {
        perror ("socket") ;
        return -1 ;
    }
    client.sun_family = AF_UNIX;
    strcpy(client.sun_path, name);

    ret_value = connect ( sock_fd, (const struct sockaddr *)&client, SUN_LEN(&client) ) ;
        if ( ret_value == -1) {
            perror("connect");
            return -1;
        }

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
