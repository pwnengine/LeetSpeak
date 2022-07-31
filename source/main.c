#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2def.h>
#include <w32api.h>
#include <ws2tcpip.h>
#include <lmcons.h>
#include "setup.h"

SOCKET listener = 0;
SOCKET sock = 0;

void cool_animation() {
  char* spaces = "                    ";
  for(int q = 0; q < 20; q++) {
    system("cls");
    printf("%sWelcome To LEETSPEAK", (spaces + 19) - q);
    Sleep(1000);
  }

  system("cls");
}

void recv_data() {
  char msg[1024];
  for(;;) {
    recv(sock, msg, sizeof(msg), 0);
    if(msg != NULL) {
      printf("%s\n", msg);
      memset(msg, 0, sizeof(msg));
    }
    Sleep(1000);
  }
}

void send_data(char* name) {
  char msg[1024];
  for(;;) {
    fgets(msg, sizeof(msg), stdin);
    if(msg != NULL) {
      printf("\n%s", msg);
      char fin_msg[1024];
      sprintf(fin_msg, "%s: %s", name, msg);
      send(sock, fin_msg, sizeof(fin_msg), 0);
      memset(msg, 0, sizeof(msg));
    }
    Sleep(1000);
  }
}

int main(void) {
  WSADATA wsadata;
  HANDLE hcon;
  char name[9];
  char ip[12];
  char port[5];
  int opt;

  hcon = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hcon, 3);

  ZeroMemory(&wsadata, sizeof(wsadata));
  if(WSAStartup(MAKEWORD(2,2), &wsadata)) {
    printf("WSAStartup() [FAILED]\n");
  }

  printf(" Enter A Name: ");
  scanf("%8s", name);

  cool_animation();

  printf(" Start A Server [1] | Join A Server [2]\n>");
  scanf("%d", &opt);
  
  if(opt == 1) {
    printf( " Enter Port: ");
    scanf("%4s", port);
    server_setup(&listener, &sock, port);
  }
  else if(opt == 2) {
    printf(" Enter IP: ");
    scanf("%11s", ip);
    printf( "\n Enter Port: ");
    scanf("%4s", port);
    client_setup(&sock, ip, port);
  }

  system("cls");
  
  CreateThread(0, 0, (LPTHREAD_START_ROUTINE)recv_data, 0, 0, 0);
  send_data(name);

  CloseHandle(hcon);
  
  return 0;
}
