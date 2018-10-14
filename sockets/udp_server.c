#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
 #include <arpa/inet.h>





int main()
{
    struct sockaddr_in server, client;
    int fd, ret_value, fd_clnt;
    int len;
    char *ptr;
    char buf[1024];





    fd = socket(AF_INET, SOCK_DGRAM, 0);

      if ( (-1) == fd ) {
            perror("socket");
            return -1;
      }

      client.sin_family = AF_INET;
      client.sin_port = htons(4000);
      client.sin_addr.s_addr = inet_addr("127.0.0.1");

    
   
      ret_value = bind (fd, (struct sockaddr *) &client, sizeof(client));


      if ( (-1) == ret_value ) {
            perror("bind");
            return -1;
      }

        len = sizeof(struct sockaddr);

/*      ret_value = listen(fd , 5);
        

      if ( (-1) == ret_value ) {
            perror("listen");
            return -1;
      }
*/
      printf("\n waiting for client  \n");

 
/*     fd_clnt = accept ( fd, (struct sockaddr *)&server, (socklen_t *)&len )     ;
       
      if ( (-1) == fd_clnt ) {
            perror("accept");
            return -1;
      }*/
        printf("\n  communicating with client \n");

        while (1)
        {
            ret_value = recvfrom (fd, buf, sizeof(buf),0, (struct sockaddr *)&client, &len);

      if ( (-1) == ret_value ) {
            perror("recvfrom");
            return -1;
                 }
        printf("\n %s  \n", buf);

           ptr = fgets (buf, sizeof(buf), stdin);
       

      if ( NULL  == ptr ) {
            perror("fgets");
            return -1;
      }
             ret_value = sendto(fd, buf, sizeof(buf), 0, (struct sockaddr *) &client, sizeof(struct sockaddr));


      if ( (-1) == ret_value ) {
            perror("sendto");
            return -1;
      }
        }

        return 0;
}
