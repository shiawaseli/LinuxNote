#ifndef _UDPSOCKET_HPP_
#define _UDPSOCKET_HPP_ 

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
  void _makeAddr(struct sockaddr_in *addr, const std::string& ip, const uint16_t port)
  {
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &addr->sin_addr.s_addr);
    memset(addr->sin_zero, 0, sizeof(addr->sin_zero));
    // inet_aton(ip.c_str(), &addr->sin_addr);
    // addr->sin_addr.s_addr = inet_addr(ip.c_str());
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
    struct sockaddr_in addr;
    _makeAddr(&addr, ip, port);
    int ret = bind(m_sockfd, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
      perror("bind error");
      return false;
    }
    return true;
  }

  bool Recv(std::string &buf, std::string *ip = nullptr, uint16_t *port = nullptr)
  {
    char Buf[BUFSIZ] = { 0 };
    struct sockaddr_in tmpaddr;
    socklen_t tmplen = sizeof(struct sockaddr_in);
    int ret = recvfrom(m_sockfd, Buf, BUFSIZ, 0, (struct sockaddr*)&tmpaddr, &tmplen);
    if (ret < 0) {
      perror("recvfrom error");
      return false;
    }
    buf = Buf;
    if (ip)
      *ip = inet_ntoa(tmpaddr.sin_addr);
    if (port)
      *port = ntohs(tmpaddr.sin_port);
    return true;
  }

  bool Send(const std::string &buf, const std::string &ip, const uint16_t port)
  {
    struct sockaddr_in addr;
    _makeAddr(&addr, ip, port);
    int ret = sendto(m_sockfd, buf.c_str(), buf.size(), 0, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
      perror("sendto error");
      return false;
    }
    return true;
  }

  bool Close()
  {
    int ret = close(m_sockfd);
    if (ret < 0) {
      perror("close error");
      return false;
    }
    return true;
  }
};

#endif /* _UDPSOCKET_HPP_ */
