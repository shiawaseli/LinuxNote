#include "my_sem.h"

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t resource = PTHREAD_COND_INITIALIZER;
static int *limit_book, limit_cnt;

int sem_init_my(sem_my *sem, int shared, unsigned int value)
{
    int i;
    for (i = 1; i < limit_cnt; i += 2) {
        if (limit_book[i] == 0) {
            *sem = i;
            limit_book[2 * (*sem)] = value;
            limit_book[2 * (*sem) + 1] = value;
            return 0;
        }
    }
    *sem = limit_cnt;
    limit_book = (int*)realloc(limit_book, ++limit_cnt * 2);
    limit_book[2 * (*sem)] = value;
    limit_book[2 * (*sem) + 1] = value;
    shared = 0;
    return 0;
}

int sem_destroy_my(sem_my *sem)
{
    limit_book[2 * (*sem)] = 0;
    limit_book[2 * (*sem) + 1] = 0;
    *sem = -1;
    return 0;
}

int sem_wait_my(sem_my *sem)
{
    if (limit_book[2 * (*sem)] == 0) {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&resource, &mutex);
        pthread_mutex_unlock(&mutex);
    }
    limit_book[2 * (*sem)]--;
    return 0;
}

int sem_post_my(sem_my *sem)
{
    pthread_mutex_lock(&mutex);
    limit_book[2 * (*sem)]++;
    pthread_mutex_unlock(&mutex);
    pthread_cond_signal(&resource);
    return 0;
}
