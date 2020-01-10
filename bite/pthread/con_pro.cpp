// 使用信号量实现生产者与消费者模型
#include <cstdio>
#include <cstdlib>
#include <pthread.h>
#include <vector>
#include <semaphore.h>

#define MAX_QUEUE 5

class RingQueue
{
public:
    RingQueue(int maxq = MAX_QUEUE) : 
        _array(maxq),
        _capacity(maxq), 
        _pos_write(0), 
        _pos_read(0) 
    {
        sem_init(&_sem_data, 0, 0); // 数据资源计数器
        sem_init(&_sem_space, 0, maxq); // 空闲空间计数器
        sem_init(&_sem_lock, 0, 1); // 锁的初始化
    }
    ~RingQueue()
    {
        sem_destroy(&_sem_data);
        sem_destroy(&_sem_space);
        sem_destroy(&_sem_lock);
    }
    bool Push(int &data)
    {
        // 没有空闲空间则直接阻塞，否则空闲空间计数-1
        sem_wait(&_sem_space); // 直接通过自身计数判断是否阻塞
        
        sem_wait(&_sem_lock); // 加锁，保护入队操作
        _array[_pos_write] = data;
        _pos_write = (_pos_write + 1) % _capacity;
        sem_post(&_sem_lock); // 解锁

        sem_post(&_sem_data);
        return true;
    }
    bool Pop(int *data)
    {
        sem_wait(&_sem_data); // 通过资源计数判断是否能获取资源
        
        sem_wait(&_sem_lock);
        *data = _array[_pos_read];
        _pos_read = (_pos_read + 1) % _capacity;
        sem_post(&_sem_lock);

        sem_post(&_sem_space);
        return true;
    }
private:
    std::vector<int> _array; // 数组
    int _capacity; // 数组的节点数量
    int _pos_write; // 写指针当前位置，写入数据后，写指针向后移动
    int _pos_read; // 读指针当前位置，读取数据后，读指针向后移动
    sem_t _sem_space; // 空闲空间计数器，有多少个空闲空间，就可以生产多少个数据
    sem_t _sem_data; // 数据资源计数器，有多少个数据资源，就可以获取多少个数据                        
    sem_t _sem_lock; // 实现安全的锁
};

#define MAX_THR 4

void* productor(void *arg)
{
    int i = 0;
    RingQueue *q = (RingQueue*)arg;

    while (1) {
        // 生产者入队数据
        q->Push(i);
        printf("productor %p --- put data: %d\n", (void*)pthread_self(), i++);
    }
    return NULL;
}

void* consumer(void *arg)
{
    int data = 0;
    RingQueue *q = (RingQueue*)arg;

    while (1) {
        // 消费者入队数据
        q->Pop(&data);
        printf("consumer %p --- get data: %d\n", (void*)pthread_self(), data);
    }
    return NULL;
}

int main()
{
    int i, ret;
    RingQueue q;
    pthread_t ptid[MAX_THR], ctid[MAX_THR];

    for (i = 0; i < MAX_THR; i++) {
        ret = pthread_create(&ptid[i], NULL, productor, (void*)&q);
        if (ret != 0) {
            printf("thread create error\n");
            return -1;
        }
    }
    for (i = 0; i < MAX_THR; i++) {
        ret = pthread_create(&ctid[i], NULL, consumer, (void*)&q);
        if (ret != 0) {
            printf("thread create error\n");
            return -1;
        }
    }
    for (i = 0; i < MAX_THR; i++) {
        pthread_join(ptid[i], NULL);
        pthread_join(ctid[i], NULL);
    }

    return 0;
}
