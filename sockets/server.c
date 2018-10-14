#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(void) 
{
    int welcomesoc, newsoc , c;

    struct sockaddr_in server, client;
    char buffer[1024];

    welcomesoc = socket(AF_UNIX, SOCK_STREAM, 0);
    server.sin_family = AF_UNIX;
    server.sin_port = htons(7767);
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    bind(welcomesoc, (struct sockaddr *) &server, sizeof(server));
   if ( listen(welcomesoc, 2) == 0) 
       printf("\n listening  \n");
   else 
       printf("\n error  \n");

   newsoc = accept(welcomesoc, (struct sockaddr *) &client, (socklen_t*)&c);
   while (1) {
      read(newsoc, buffer, sizeof(buffer));
      printf("\n client : %s  \n", buffer);
       fgets(buffer, sizeof(buffer), stdin);

        write(newsoc, buffer, 1024);
   }
return 0;
}
