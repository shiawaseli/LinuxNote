#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include "my_sem.h"

#define NUM 5
int queue[NUM];
sem_my blank_number, product_number;

void* producer(void *arg)
{
    int p = 0;
    while (1) {
        sem_wait_my(&blank_number);
        queue[p] = rand() % 1000 + 1;
        printf("Produce %d\n", queue[p]);
        sem_post_my(&product_number);
        p = (p + 1) % NUM;
        usleep(rand() % 5);
    }
}

void* consumer(void *arg)
{
    int c = 0;
    while (1) {
        sem_wait_my(&product_number);
        printf("Consume %d\n", queue[c]);
        queue[c] = 0;
        sem_post_my(&blank_number);
        c = (c + 1) % NUM;
        sleep(rand() % 5);
    }
}

int main()
{
    pthread_t pid, cid;

    sem_init_my(&blank_number, 0, NUM);
    sem_init_my(&product_number, 0, 0);
    pthread_create(&pid, NULL, producer, NULL);
    pthread_create(&cid, NULL, consumer, NULL);
    pthread_join(pid, NULL);
    pthread_join(cid, NULL);
    sem_destroy_my(&blank_number);
    sem_destroy_my(&product_number);

    return 0;
}
