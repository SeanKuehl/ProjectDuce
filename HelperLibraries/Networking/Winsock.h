#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#define ERROR -1
#define SUCCESS 1
#define BUFFER_SIZE 255

#include<stdio.h>
#include<winsock2.h>
#include <string>

#pragma comment(lib,"ws2_32.lib") //Winsock Library
using namespace std;



int InitializeWinsock();

SOCKET CreateSocket();

int ConnectToServer(SOCKET s, string ip, int port);

int SendString(SOCKET s, string message);

int BindServer(SOCKET s, int port);

SOCKET AcceptConnection(SOCKET s);

string ReceiveString(SOCKET new_socket);