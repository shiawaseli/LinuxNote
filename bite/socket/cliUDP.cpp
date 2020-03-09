#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <cstdlib>
#include <unistd.h>

class UDPsocket
{
private:
  int m_sockfd;
private:
  struct sockaddr_in _makeAddr(const std::string& ip, const uint16_t port)
  {
    struct sockaddr_in addr;

    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr.sin_addr.s_addr);
    
    return addr;
  }
public:
  bool Socket()
  {
    m_sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_sockfd < 0) {
      perror("socket error");
      return false;
    }
    return true;
  }

  bool Bind(const std::string &ip, const uint16_t port)
  {
    auto addr = _makeAddr(ip, port);
    int ret = bind(m_sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
      perror("bind error");
      return false;
    }
    return true;
  }

  bool Recv(std::string &buf, struct sockaddr_in *addr = nullptr, socklen_t *len = nullptr)
  {
    char Buf[4098];
    struct sockaddr_in tmpaddr;
    socklen_t tmplen;
    int ret = recvfrom(m_sockfd, Buf, 4098, 0, (struct sockaddr*)&tmpaddr, &tmplen);
    if (ret < 0) {
      perror("recvfrom error");
      return false;
    }
    buf.assign(Buf, strlen(Buf));
    if (addr)
      *addr = tmpaddr;
    if (len)
      *len = tmplen;
    return true;
  }

  bool Send(const std::string &buf, const std::string &ip, const uint16_t port)
  {
    auto addr = _makeAddr(ip, port);
    socklen_t len = sizeof(struct sockaddr_in);
    int ret = sendto(m_sockfd, buf.c_str(), buf.size(), 0, (struct sockaddr*)&addr, len);
    if (ret < 0) {
      perror("sendto error");
      return false;
    }
    return true;
  }

  bool Close()
  {
    close(m_sockfd);
    return true;
  }
};


int main(int argc, char *argv[])
{
  if (argc != 3) {
    printf("argument like: ./cliUDP 172.17.223.241 9000\n");
    return 1;
  }
  std::string ip = argv[1];
  uint16_t port = atoi(argv[2]);

  UDPsocket test;
  test.Socket();

  while (1) {
    std::string buf;
    std::cout << "请输入要发往服务器的内容: ";
    std::cin >> buf;
    if (!test.Send(buf, ip, port)) {
      test.Close();
      return 1;
    }
    buf.clear();
    if (!test.Recv(buf)) {
      test.Close();
      return 1;
    }
    std::cout << "回复: " << buf << std::endl;
  }
  test.Close();
  return 0;
}
