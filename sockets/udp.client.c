#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<string.h>

int main()
{
    struct sockaddr_in client;
    int fd,len, ret_value;
    char buffer[1024];
    int length;    
    char *ptr;


    fd = socket(AF_INET, SOCK_DGRAM, 0);
      
    if ( (-1) == fd ) {
            perror("socket");
            return -1;
      }
        length = sizeof(socklen_t);     
    client.sin_family = AF_INET;
    client.sin_port = htons(4000);
    client.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1)
    {
        printf("\n  enter the message \n");
        ptr = fgets (buffer, sizeof(buffer), stdin);
//        printf("\n  hai \n");
           ret_value = sendto(fd, buffer, 1024,0, (struct sockaddr*)&client, sizeof(struct sockaddr));
            
    if ( (-1) == ret_value ) {
            perror("sendto");
            return -1;
      }

           recvfrom(fd, buffer, 1024, 0, (struct sockaddr *)&client, &len);
           printf("\n received %s  \n", buffer);



    }
    
           return 0;
}
