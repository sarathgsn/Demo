#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
pthread_spinlock_t lock1;
pthread_t tid[2];
int counter;
pthread_mutex_t lock;

void* trythis(void *arg)
{
//    pthread_mutex_lock(&lock);
    pthread_spin_lock(&lock1);
    unsigned long i = 0;
    counter += 1;
    printf("\n Job %d has started\n", counter);

    for(i=0; ;i++);

    printf("\n Job %d has finished\n", counter);
    pthread_spin_unlock(&lock1);
  //  pthread_mutex_unlock(&lock);

    return NULL;
}

int main(void)
{
    int i = 0;
    int error;
    pthread_spin_init(&lock1, 1);
    if (pthread_mutex_init(&lock, NULL) != 0)
    {
        printf("\n mutex init has failed\n");
        return 1;
    }

    while(i < 16)
    {
        error = pthread_create(&(tid[i]), NULL, &trythis, NULL);
        if (error != 0)
            printf("\nThread can't be created :");
        i++;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}
