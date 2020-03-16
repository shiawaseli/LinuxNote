#include "TCPsocket.hpp"
#include <iostream>
#include <sys/wait.h>
#include <signal.h>

void sigChld(int)
{
  // waitpid() > 0 表示有子进程退出--若返回值<=0则表示没有子进程退出了
  // WNOHANG--非阻塞操作
  // SIGCHLD信号是一个非可靠信号有可能丢失事件-因此循环处理到把已经退出的完全处理完毕
  while (waitpid(-1, NULL, WNOHANG) > 0) {
    continue;
  }
}

int main(int argc, char *argv[])
{
  if (argc != 3) {
    perror("argument like: ./processServTCP 172.17.223.241 9000");
    return 1;
  }
  // 对SIGCHLD信号自定义处理，等到子进程退出的时候处理一下就可以
  // 这样就避免了父进程一直等待的情况
  signal(SIGCHLD, sigChld); // 自定义信号处理函数
  std::string ip = argv[1], newIp;
  uint16_t port = atoi(argv[2]), newPort = 0;
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
    int newSockfd = 0;
    std::string buf;
    if (!sockfd.Accept(newSockfd, &newIp, &newPort)) { // 获取新连接
      continue; // 服务端不会因为一次获取的失败而退出，而是继续重新获取下一个
    }

    pid_t pid = fork();
    if (pid == 0) { // 每个子进程负责与一个客户端进行循环通信
      TCPsocket cliSock;
      cliSock.setSocket(newSockfd);
      while (1) {
        if (!cliSock.Recv(buf)) { // 通过新连接接收数据
          cliSock.Close();
          exit(1);
        }
        std::cout << "[" << newIp.c_str() << ":" << newPort << "]client say: " << buf << std::endl;
        std::cout << "server say: ";
        std::cin >> buf;
        if (!cliSock.Send(buf)) { // 通过新连接发送数据
          cliSock.Close();
          exit(1);
        }
      }
      cliSock.Close();
      exit(0);
    }
  }
  sockfd.Close();

  return 0;
}
