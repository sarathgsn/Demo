#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
 #include <unistd.h>
#include <arpa/inet.h>

int main(void) 
{
    int client_socket;
    char buffer[1024];
    socklen_t addr_size;
    struct sockaddr_in serveradds;

    client_socket = socket(AF_UNIX, SOCK_STREAM,0);
    serveradds.sin_family = AF_UNIX;
    serveradds.sin_port = htons(7767);
    serveradds.sin_addr.s_addr = inet_addr("127.0.0.1");
    connect(client_socket, (struct sockaddr *) &serveradds, addr_size);
printf("\n  client :connection established \n");
 while(1) {
     fgets(buffer, sizeof(buffer), stdin);

    write(client_socket, buffer, 1024);
    read(client_socket, buffer, sizeof(buffer));
    printf(" data received %s ::", buffer);
    return 0;
    }

}

