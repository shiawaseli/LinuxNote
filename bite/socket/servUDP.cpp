#include <iostream>
#include "UDPsocket.hpp"

int main(int argc, char *argv[])
{
  if (argc != 3) {
    std::cout << "argument like: ./servUDP 172.17.223.241 9000" << std::endl;
    return 1;
  }
  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);
  UDPsocket sockfd;
  if (!sockfd.Socket()) {
    return 1;
  }
  if (!sockfd.Bind(ip, port)) {
    return 1;
  }
  
  while (1) {
    std::string buf, cliIp;
    uint16_t cliPort;
    
    if (!sockfd.Recv(buf, &cliIp, &cliPort)) {
      sockfd.Close();
      return 1;
    }
    printf("[%s:%d]client say: %s\n", cliIp.c_str(), cliPort, buf.c_str());
    std::cout << "server say: ";
    std::cin >> buf;
    if (!sockfd.Send(buf, cliIp, cliPort)) {
      sockfd.Close();
      return 1;
    }
  }

  return 0;
}
