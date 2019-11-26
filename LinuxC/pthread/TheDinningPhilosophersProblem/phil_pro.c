#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int chops[5] = { 1, 1, 1, 1, 1 };
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t chop1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t chop2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t chop3 = PTHREAD_COND_INITIALIZER;
pthread_cond_t chop4 = PTHREAD_COND_INITIALIZER;
pthread_cond_t chop5 = PTHREAD_COND_INITIALIZER;
pthread_cond_t *(conds[5]) = { &chop1, &chop2, &chop3, &chop4, &chop5 };

void* philosopher(void *philno)
{
    int no = *(int*)philno;
    while (1) {
        usleep(rand() % 10);

        pthread_mutex_lock(&mutex);
        if (chops[(no + 3) % 5] == 0)
            pthread_cond_wait(conds[(no + 3) % 5], &mutex);
        chops[(no + 3) % 5] = 0;
        printf("Philosopher %c fetches chopstick %d\n", " ABCDE"[no], (no + 3) % 5 + 1);
        // pthread_mutex_unlock(&mutex);

        // pthread_mutex_lock(&mutex);
        if (chops[no - 1] == 0)
            pthread_cond_wait(conds[no - 1], &mutex);
        chops[no - 1] = 0;
        printf("Philosopher %c fetches chopstick %d\n", " ABCDE"[no], no);
        pthread_mutex_unlock(&mutex);

        printf("Philosopher %c releases chopsticks %d %d\n", " ABCDE"[no], (no + 3) % 5 + 1, no);
        pthread_mutex_lock(&mutex);
        chops[(no + 3) % 5] = 1;
        chops[no - 1] = 1;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(conds[(no + 3) % 5]);
        pthread_cond_signal(conds[no - 1]);
        
        usleep(rand() % 10);
    }
    return NULL;
}

int main()
{
    int num[5] = { 1, 2, 3, 4, 5 };
    pthread_t tid1, tid2, tid3, tid4, tid5;
    srand((unsigned int)time(NULL));
    pthread_create(&tid1, NULL, philosopher, &num[0]);
    pthread_create(&tid2, NULL, philosopher, &num[1]);
    pthread_create(&tid3, NULL, philosopher, &num[2]);
    pthread_create(&tid4, NULL, philosopher, &num[3]);
    pthread_create(&tid5, NULL, philosopher, &num[4]);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
    pthread_join(tid3, NULL);
    pthread_join(tid4, NULL);
    pthread_join(tid5, NULL);
    return 0;
}
