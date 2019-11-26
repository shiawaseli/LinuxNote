#ifndef _MY_SEM_H_

#define _MY_SEM_H_ 

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

typedef int sem_my;

int sem_init_my(sem_my *sem, int shared, unsigned int value);
int sem_destroy_my(sem_my *sem);
int sem_wait_my(sem_my *sem);
int sem_post_my(sem_my *sem);

#endif /* _MY_SEM_H_ */ 
