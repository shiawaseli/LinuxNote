#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXSIZE 5
int queue[MAXSIZE];
sem_t blank, full;

void* producer(void *p)
{
    int top = 0;

    while (1) {
        sem_wait(&blank);
        queue[top] = rand() % 10 + 1;
        sem_post(&full);
        printf("Produce %d\n", queue[top]);
        top = (top + 1) % MAXSIZE;
        sleep(rand() % 3);
    }
}

void* consumer(void *p)
{
    int top = 0;

    while (1) {
        sem_wait(&full);
        printf("Consumer %d\n", queue[top]);
        queue[top] = 0;
        sem_post(&blank);
        top = (top + 1) % MAXSIZE;
        sleep(rand() % 3);
    }
}

int main()
{
    pthread_t tid1, tid2;
    srand((unsigned int)time(NULL));

    sem_init(&blank, 0, 5);
    sem_init(&full, 0, 0);
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    sem_destroy(&blank);
    sem_destroy(&full);
    
    return 0;
}
