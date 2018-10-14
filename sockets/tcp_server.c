
/* TCP server program */
#include<pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define MAX 100
void *function(int *);

int main(void)

{   
    int i , j ;
     i = j = 1;
     int pid;
    int sock_fd ;
    int sock_fd_clnt ;
    struct sockaddr_in v_bnd ;
    struct sockaddr_in v_acpt ;
    int len ;
    int ret_value ;
    char *ptr ;
    char buf[MAX] ;
    pthread_t thread;

    sock_fd = socket ( AF_INET, SOCK_STREAM, 0 ) ;

    if ( (-1) == sock_fd ) {
        perror ("socket") ;
        return -1 ;
    }

    v_bnd.sin_family = AF_INET ;
    v_bnd.sin_port = htons (4000) ;
    v_bnd.sin_addr.s_addr = inet_addr ("127.0.0.1");

    len = sizeof(v_bnd) ;

    ret_value = bind ( sock_fd, (const struct sockaddr *)&v_bnd, (socklen_t)len ) ;

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

    while ( 1 ) {
 
        sock_fd_clnt = accept ( sock_fd, (struct sockaddr *)&v_acpt, (socklen_t *)&len ) ;

    if ( (-1) == sock_fd_clnt ) {
        perror ("accept") ;
        return -1 ;
    }

    printf ("server : Connection established \n") ;

     
     ret_value =  pthread_create(&thread, NULL, function, &sock_fd_clnt);

     if ( ret_value != 0) 
     {
         perror("pthread_create");
         return -1;
     
     
     }

            }
         

return 0;
}



     
void* function(int *ptr)
{
     char buf[1024];
    int ret_value;
    char *str;
    pthread_t id;
    while(1) {

       id =  pthread_self();
       printf("\n thread id is %d  \n", id);
        ret_value = read ( *ptr, buf, sizeof (buf) ) ;

        if ( (-1) == ret_value ) {
            perror ("read") ;
  //          return -1 ;
        }

        printf ("client : %s \n", buf) ;

        str = fgets ( buf, sizeof (buf), stdin ) ;

        if ( NULL == ptr ) {
            perror ("fgets") ;
//             return -1 ;
        }
 
        ret_value = write ( *ptr, buf, sizeof (buf) ) ;

        if ( (-1) == ret_value ) {
            perror ("write") ;
    //        return -1 ;
        }
        

    }
  }
   




/*

        sock_fd_clnt = accept ( sock_fd, (struct sockaddr *)&v_acpt, (socklen_t *)&len ) ;

 

    if ( (-1) == sock_fd_clnt ) {
        perror ("accept") ;
        return -1 ;
    }

    printf ("server : Connection established \n") ;

     
    
    while ( 1 ) {

    
        ret_value = read ( sock_fd_clnt, buf, sizeof (buf) ) ;

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
 
        ret_value = write ( sock_fd_clnt, buf, sizeof (buf) ) ;

        if ( (-1) == ret_value ) {
            perror ("write") ;
            return -1 ;
        }
         j++;
        }

return 0;
        }
*/
  
