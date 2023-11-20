#include <iostream>
#include <string>
#include "Network.h"

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main()
{
   SetConsoleCP(1251);//кириллица в консоли
   SetConsoleOutputCP(1251);

   InitLibrary();//инициализация библиотек для работы с сокетами

   SOCKET sock = InitSock();//инициализация сокета
   string hostname;

   cout << "Введите имя хоста или IP-адрес: ";
   cin >> hostname;
   string host;

   IPAddr ipaddr;
   ConvertHostName(hostname, host, ipaddr);//hostname - имя домена, host - адрес ip, ipaddr-хранит адрес для последующих запросов
   cout

      << "\n\nОбмен пакетами с " << hostname << " [" << host << "] "
      << "c " << BufferSize + sizeof(ICMP_ECHO_REPLY)
      << " байтами данных:\n";

   MakeRequest(ipaddr, host);
}