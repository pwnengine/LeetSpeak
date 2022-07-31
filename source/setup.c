#include "setup.h"

void server_setup(SOCKET* listener, SOCKET* sock, const char* port) {
  struct addrinfo hints;
  struct addrinfo* ai;
  ZeroMemory(&hints, sizeof(hints));

  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  if(getaddrinfo(0, port, &hints, &ai)) {
    printf("getaddrinfo() [FAILED]\n");
    WSACleanup();
  }
  
  *listener = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
  if(listener == 0) {
    printf("socket() [FAILED]\n");
    freeaddrinfo(ai);
    WSACleanup();
  }
  
  if(bind(*listener, ai->ai_addr, ai->ai_addrlen) == SOCKET_ERROR) {
    printf("socket() [FAILED]\n");
    freeaddrinfo(ai);
    closesocket(*listener);
    WSACleanup();
  }
  freeaddrinfo(ai);

  if(listen(*listener, SOMAXCONN) == SOCKET_ERROR) {
    printf("listen() [FAILED]\n");
    closesocket(*listener);
    WSACleanup();
  }

  *sock = accept(*listener, 0, 0);
}

void client_setup(SOCKET* sock, const char* ip, const char* port) {
  struct addrinfo hints;
  struct addrinfo* ai;
  ZeroMemory(&hints, sizeof(hints));

  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  if(getaddrinfo(ip, port, &hints, &ai)) {
    printf("getaddrinfo() [FAILED]\n");
    WSACleanup();
  }
  
  *sock = socket(ai->ai_family, ai->ai_socktype, ai->ai_protocol);
  if(*sock == 0) {
    printf("socket() [FAILED]\n");
    freeaddrinfo(ai);
    WSACleanup();
  }
  
  while(connect(*sock, ai->ai_addr, ai->ai_addrlen) != 0) {
    Sleep(5000);
  }
  
  freeaddrinfo(ai);
}
