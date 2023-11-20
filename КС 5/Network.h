#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
 
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
 
#include <icmpapi.h>
#include <iostream>
#include <string>
 
using namespace std;
const int BufferSize = 4;//размер буфера
 
const int requestCount = 4;//сколько пакетов посылаем
const char TTL = 64;//время жизни пакета
 
void InitLibrary();
 
SOCKET InitSock();
 
bool ConvertHostName(string& hostname, string& host, IPAddr& ipaddr); 
void MakeRequest(IPAddr ipaddr, string& host);