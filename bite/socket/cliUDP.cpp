#include "UDPsocket.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("argument like: ./cliUDP 172.17.223.241 9000\n");
    return 1;
  }
  std::string servIp = argv[1];
  uint16_t servPort = atoi(argv[2]);

  UDPsocket test;
  test.Socket();

  while (1) {
    std::string buf;
    std::cout << "请输入要发往服务器的内容: ";
    std::cin >> buf;
    if (!test.Send(buf, servIp, servPort)) {
      test.Close();
      return 1;
    }
    buf = std::string();
    if (!test.Recv(buf)) {
      test.Close();
      return 1;
    }
    std::cout << "回复: " << buf.c_str() << std::endl;
  }
  test.Close();
  return 0;
}
