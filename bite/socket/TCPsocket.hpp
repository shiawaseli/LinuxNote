#ifndef _TCPSOCKET_HPP_
#define _TCPSOCKET_HPP_ 

#include <string>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

const int MAXLISTEN = 10;

class TCPsocket 
{
private:
  int m_socket;
private:
  void _makeAddr(struct sockaddr_in *addr, const std::string &ip, const uint16_t port)
  {
    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);
    inet_aton(ip.c_str(), &addr->sin_addr);
    memset(addr->sin_zero, 0, sizeof(addr->sin_zero));
    // inet_pton(AF_INET, ip.c_str(), &addr->sin_addr.s_addr);
    // addr->sin_addr.s_addr = inet_addr(ip.c_str());
  }
public:
  TCPsocket() : m_socket(-1) { }
  bool Socket()
  {
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket < 0) {
      perror("socket error");
      return false;
    }
    return true;
  }
  
  bool Bind(const std::string &ip, const uint16_t port)
  {
    struct sockaddr_in addr;
    _makeAddr(&addr, ip, port);
    int ret = bind(m_socket, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
      perror("bind error");
      return false;
    }
    return true;
  }

  bool Listen()
  {
    int ret = listen(m_socket, MAXLISTEN);
    if (ret < 0) {
      perror("listen error");
      return false;
    }
    return true;
  }

  bool Accept(int &newSock, std::string *ip = nullptr, uint16_t *port = nullptr)
  {
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);
    newSock = accept(m_socket, (struct sockaddr*)&addr, &len);
    if (newSock < 0) {
      perror("accept error");
      return false;
    }
    if (ip) {
      *ip = inet_ntoa(addr.sin_addr);
    }
    if (port) {
      *port = ntohs(addr.sin_port);
    }

    return true;
  }

  bool Connect(const std::string &ip, const uint16_t port)
  {
    struct sockaddr_in addr;
    _makeAddr(&addr, ip, port);
    int ret = connect(m_socket, (struct sockaddr*)&addr, sizeof(struct sockaddr_in));
    if (ret < 0) {
      perror("connect error");
      return false;
    }
    return true;
  }

  bool Send(const std::string &buf)
  {
    int ret = send(m_socket, buf.c_str(), strlen(buf.c_str()), 0);
    if (ret < 0) {
      perror("send error");
      return false;
    }
    return true;
  }

  bool Recv(std::string &buf)
  {
    char Buf[BUFSIZ] = { 0 };
    int ret = recv(m_socket, Buf, BUFSIZ, 0);
    if (ret < 0) {
      perror("recv error");
      return false;
    } else if (ret == 0) {
      printf("connection break");
      return false;
    }
    buf = Buf;
    return true;
  }

  bool Close()
  {
    int ret = close(m_socket);
    if (ret < 0) {
      perror("close error");
      return false;
    }
    return true;
  }

  int getSocket() {
    return m_socket;
  }

  void setSocket(int socket) {
    m_socket = socket;
  }
};

#endif /* _TCPSOCKET_HPP_ */ 
