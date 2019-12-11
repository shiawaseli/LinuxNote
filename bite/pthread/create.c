#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *thread_start(void *arg)
{
    // 进入后立即分离当前线程
    // pthread_detach(pthread_self());
    char *buf = "你好啊~";
    sleep(3);
    pthread_exit(buf);
    while (1) {
        printf("主线程传递了一个参数: %s\n", (char*)arg);
        sleep(1);
    }
    return NULL;
}

int main()
{
    pthread_t tid;
    char buf[] = "还有半个小时~";
    int ret = pthread_create(&tid, NULL, thread_start, (void*)buf);
    if (ret != 0) {
        printf("pthread create error: %d\n", ret);
        return -1;
    }
    // 创建线程后立即分离线程，分离后不能再进行线程等待
    // pthread_detach(pid);

    //sleep(3);
    //pthread_cancel(tid);
    //pthread_cancel(pthread_self());
    //pthread_exit(NULL);
    void *retval;
    pthread_join(tid, &retval);
    printf("线程退出值:[%s]\n", retval);
    while (1) {
        printf("I am main thread, child tid%p\n", tid);
        sleep(1);
    }
    return 0;
}
