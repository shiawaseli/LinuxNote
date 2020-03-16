#include "TCPsocket.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  if (argc != 3) {
    perror("argument like: ./servTCP 172.17.223.241 9000");
    return 1;
  }
  std::string ip = argv[1], newIp;
  uint16_t port = atoi(argv[2]), newPort = 0;
  TCPsocket sockfd;
  if (!sockfd.Socket()) {
    return 1;
  }
  if (!sockfd.Bind(ip, port)) {
    sockfd.Close();
    return 1;
  }
  if (!sockfd.Listen()) {
    sockfd.Close();
    return 1;
  }
  
  while (1) {
    int newSockfd = 0;
    std::string buf;
    if (!sockfd.Accept(newSockfd, &newIp, &newPort)) {
      continue;
    }
    TCPsocket cliSock;
    cliSock.setSocket(newSockfd);
    if (!cliSock.Recv(buf)) {
      cliSock.Close();
      perror("server recvdata error, disconnect!");
      continue;
    }
    std::cout << "[" << newIp.c_str() << ":" << newPort << "]client say: " << buf << std::endl;
    std::cout << "server say: ";
    std::cin >> buf;
    if (!cliSock.Send(buf)) {
      cliSock.Close();
      perror("server senddata error, disconnect!");
      continue;
    }
  }
  sockfd.Close();

  return 0;
}
