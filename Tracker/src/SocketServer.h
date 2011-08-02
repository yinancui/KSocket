#ifndef SOCKETSERVER_H_
#define SOCKETSERVER_H_

#include <winsock2.h>
#include <windows.h>

int initSocket();
//int closeSocket();

//void HandleConnection(SOCKET hClientSocket, const sockaddr_in &sockAddr, char* frameData);

#endif