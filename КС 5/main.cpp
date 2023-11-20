#include <iostream>
#include <string>
#include "Network.h"

#pragma comment(lib, "iphlpapi.lib")
#pragma comment(lib, "ws2_32.lib")
using namespace std;

int main()
{
   SetConsoleCP(1251);//��������� � �������
   SetConsoleOutputCP(1251);

   InitLibrary();//������������� ��������� ��� ������ � ��������

   SOCKET sock = InitSock();//������������� ������
   string hostname;

   cout << "������� ��� ����� ��� IP-�����: ";
   cin >> hostname;
   string host;

   IPAddr ipaddr;
   ConvertHostName(hostname, host, ipaddr);//hostname - ��� ������, host - ����� ip, ipaddr-������ ����� ��� ����������� ��������
   cout

      << "\n\n����� �������� � " << hostname << " [" << host << "] "
      << "c " << BufferSize + sizeof(ICMP_ECHO_REPLY)
      << " ������� ������:\n";

   MakeRequest(ipaddr, host);
}