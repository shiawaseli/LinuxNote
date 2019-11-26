#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct msg {
    int num;
    struct msg *next;
};

struct msg *head;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void* consumer(void *p)
{
    struct msg *tmp;

    while (1) {
        pthread_mutex_lock(&mutex);
        while (head == NULL) {
            pthread_cond_wait(&cond, &mutex);
        } 
        tmp = head;
        head = head->next;
        pthread_mutex_unlock(&mutex);
        
        printf("Consumer %d\n", tmp->num);
        free(tmp);
        sleep(rand() % 3);
    }
}

void* producer(void *p)
{
    struct msg *tmp, *cur;

    while (1) {
        tmp = (struct msg*)malloc(sizeof(struct msg));
        tmp->next = NULL;
        tmp->num = rand() % 1000 + 1;
        printf("Producer %d\n", tmp->num);

        pthread_mutex_lock(&mutex);
        if (head != NULL) {
            cur = head;
            while (cur->next) {
                cur = cur->next;
            }
            cur->next = tmp;
        } else {
            head = tmp;
        }
        pthread_mutex_unlock(&mutex);
        
        pthread_cond_signal(&cond);
        sleep(rand() % 3);
    }
}

int main()
{
    pthread_t tid1, tid2;
    srand((unsigned int)time(NULL));

    pthread_create(&tid1, NULL, consumer, NULL);
    pthread_create(&tid2, NULL, producer, NULL);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    return 0;
}
