#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

// Let us create a global variable to change it in threads
int g = 0;

  pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
// The function to be executed by all threads
void *myThreadFun(void *vargp)
{
    // Store the value argument pascanf("");ed to this thread
 int pid;
    // Let us create a static variable to observe its changes
  //  static int s = 0;
    pthread_mutex_lock(&mutex1);
    // Change static and global variables
     ++g;
     sleep(5);
     pid = pthread_self();
    printf("Thread ID: %d, Global: %d\n", pid, ++g);
//     pthread_mutex_unlock(&mutex1);

    //Print the argument, static and global variables
}

int main()
{
    int i;
    pthread_t tid;

    // Let us create three threads
    for (i = 0; i < 3; i++)
        pthread_create(&tid, NULL, myThreadFun, (void *)&i);

    pthread_exit(NULL);
    return 0;
}
