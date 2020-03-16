#include "TCPsocket.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  if (argc != 3) {
    perror("argument like: ./cliTCP 172.17.223.241 9000");
    return 1;
  }
  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  TCPsocket sockfd;
  if (!sockfd.Socket()) {
    return 1;
  }
  if (!sockfd.Connect(ip, port)) {
    sockfd.Close();
    return 1;
  }

  while (1) {
    std::string buf;
    std::cout << "请输入要发往服务器的内容: ";
    std::cin >> buf;
    if (!sockfd.Send(buf)) {
      sockfd.Close();
      perror("client senddata error, exit");
      return 1;
    }
    if (!sockfd.Recv(buf)) {
      sockfd.Close();
      perror("client recvdata error, exit");
      return 1;
    }
    std::cout << "回复: " << buf << std::endl;
  }

  return 0;
}
