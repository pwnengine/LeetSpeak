#ifndef SETUP_H
#define SETUP_H

#include <stdlib.h>
#include <stdio.h>
#include <winsock2.h>
#include <ws2def.h>
#include <w32api.h>
#include <ws2tcpip.h>
#include <lmcons.h>

void server_setup(SOCKET* listener, SOCKET* sock, const char* port);
void client_setup(SOCKET* sock, const char* ip, const char* port);

#endif
