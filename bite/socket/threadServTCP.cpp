#include "TCPsocket.hpp"
#include <iostream>
#include <sys/wait.h>
#include <signal.h>

std::string tmpIp;
uint16_t tmpPort;

void* thr_start(void *arg)
{
  int newSockfd = *(int*)arg;
  TCPsocket cliSock;
  uint16_t newPort = tmpPort;
  std::string buf, newIp = tmpIp;
  cliSock.setSocket(newSockfd);
  while (1) {
    if (!cliSock.Recv(buf)) { // 通过新连接接收数据
      cliSock.Close();
      pthread_exit(nullptr);
    }
    std::cout << "[" << newIp.c_str() << ":" << newPort << "]client say: " << buf << std::endl;
    std::cout << "server say: ";
    std::cin >> buf;
    if (!cliSock.Send(buf)) { // 通过新连接发送数据
      cliSock.Close();
      pthread_exit(nullptr);
    }
  }
  cliSock.Close();
  pthread_exit(nullptr);
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    perror("argument like: ./threadServTCP 172.17.223.241 9000");
    return 1;
  }
  // 对SIGCHLD信号自定义处理，等到子进程退出的时候处理一下就可以
  // 这样就避免了父进程一直等待的情况
  
  int newSockfd = -1;
  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  TCPsocket sockfd;
  if (!sockfd.Socket()) { // 创建套接字
    return 1;
  }
  if (!sockfd.Bind(ip, port)) { // 绑定地址信息
    sockfd.Close();
    return 1;
  }
  if (!sockfd.Listen()) { // 开始监听
    sockfd.Close();
    return 1;
  }
  
  while (1) {
    std::string buf;
    if (!sockfd.Accept(newSockfd, &tmpIp, &tmpPort)) { // 获取新连接
      continue; // 服务端不会因为一次获取的失败而退出，而是继续重新获取下一个
    }

    pthread_t tid;
    pthread_create(&tid, nullptr, thr_start, &newSockfd);
    pthread_detach(tid); // 线程退出后直接自动释放资源
  }
  sockfd.Close();

  return 0;
}
