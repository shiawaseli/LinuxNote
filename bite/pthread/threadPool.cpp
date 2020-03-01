#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <queue>
#include <pthread.h>
#include <unistd.h>
using namespace std;

typedef void (*task_hander)(int);


class ThreadTask
{
private:
  int m_data;
  task_hander m_hander;
public:
  ThreadTask(task_hander hander, int data) :
    m_data(data), 
    m_hander(hander)
  { }

  void run()
  {
    m_hander(m_data);
  }
};

const size_t MAX_THREAD = 5;

class ThreadPool
{
private:
  size_t m_thrCnt;
  queue<ThreadTask> m_queue;
  pthread_mutex_t m_mutex;
  pthread_cond_t m_cond;
public:
  ThreadPool(size_t maxThr = MAX_THREAD) : m_thrCnt(maxThr)
  {
    int ret;
    pthread_t tid;

    pthread_mutex_init(&m_mutex, NULL);
    pthread_cond_init(&m_cond, NULL);

    for (size_t i = 0; i < maxThr; ++i)
    {
      ret = pthread_create(&tid, NULL, thr_start, (void*)this);
      if (ret != 0)
      {
        printf("%s\n", "create pthread error");
        exit(1);
      }

      pthread_detach(tid);
    }
  }

  ~ThreadPool()
  {
    pthread_mutex_destroy(&m_mutex);
    pthread_cond_destroy(&m_cond);
  }

  void PushTask(task_hander hander, int data)
  {
    PushTask(ThreadTask(hander, data));
  }

  void PushTask(const ThreadTask & task)
  {
    pthread_mutex_lock(&m_mutex);
    m_queue.push(task);
    pthread_mutex_unlock(&m_mutex);

    pthread_cond_signal(&m_cond);
  }

  static void* thr_start(void *arg)
  {
    ThreadPool *pool = (ThreadPool*)arg;

    while (1)
    {
      pthread_mutex_lock(&pool->m_mutex);
      while (pool->m_queue.empty())
        pthread_cond_wait(&pool->m_cond, &pool->m_mutex);
      ThreadTask task = pool->m_queue.front();
      pool->m_queue.pop();
      pthread_mutex_unlock(&pool->m_mutex);

      task.run();
    }
    
    return NULL;
  }
    
};

void show(int data)
{
  srand(time(NULL));
  int sec = rand() % 5;
  printf("pthread %p get data %d sleep %d\n", pthread_self(), data, sec);
  sleep(sec);
}

int main()
{
  ThreadPool pool;

  for (int i = 0; i < 10; ++i)
  {
    pool.PushTask(&show, i);
  }

  while (1)
    sleep(1);

  return 0;
}
