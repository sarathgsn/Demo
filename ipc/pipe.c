#include<stdio.h>
#include<unistd.h>

int main(void)
{
    int fd[2];
    char str[100];
    pipe(fd);
    printf("%d\n", fd[0]);

    printf("%d\n", fd[1]);
    pid_t pid = fork();

    if(pid > 0){  // parent process
        close(fd[0]);
        printf("in parent enter data\n");
        
        scanf("%s", str);
       
      //  read(fd[0], str, 10);
      //  printf(" parent: %s\n", str);
        write(fd[1], str, 10);
    }
    else if(pid == 0){ //child process

        close(fd[1]);
      //  sleep(5);
        printf("in child\n");
      //  scanf("%s", str);

    //    write(fd[1], str, sizeof(str));
        read(fd[0], str, 10);
    //    printf("child : %s\n", str);
    }

    else {
        printf("fork failed\n");
    }


    return 0;
}
