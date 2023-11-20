#include "Network.h"


void InitLibrary()
{
   WSAData wsaData;
   WSAStartup(MAKEWORD(2, 2), &wsaData);
}

SOCKET InitSock()
{

   SOCKET sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP); setsockopt(sock, IPPROTO_IP, IP_TTL, &TTL, sizeof(TTL)); return sock;
}

bool ConvertHostName(string& hostname, string& host, IPAddr& ipaddr)
{

   hostent* host_entity = gethostbyname(hostname.c_str()); if (host_entity == nullptr)//host_ent - ��� �������� ���������� �� ����
      return false;

   in_addr* addr = (in_addr*)(host_entity->h_addr_list[0]); //�������� ����� � in_addr �� hostent
   host = inet_ntoa(*addr);//� host ������� "�������������" �����
   inet_pton(AF_INET, host.c_str(), &ipaddr);//� ipaddr ������� �������� ������������� host
   

}

void MakeRequest(IPAddr ipaddr, string& host)//������ � ������

{
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

   int min = 1000, average = 0, max = 0, sent = 0, received = 0; char* buffer = new char[BufferSize];

   for (int i = 0; i < BufferSize; i++)//��������� ����� �������
      buffer[i] = rand();
   HANDLE hIcmpFile = IcmpCreateFile();//��������� ���������� �� ������� ����� ������ ���-������� ipv4

   int ReplySize = sizeof(ICMP_ECHO_REPLY) + BufferSize; char* ReplyBuffer = new char[ReplySize];//������ ������ � ����� ������
   for (int i = 0; i < requestCount; ++i)

   {

      int result = IcmpSendEcho(hIcmpFile, ipaddr, buffer, BufferSize, NULL, ReplyBuffer, ReplySize, 1000);//����� - 1000

      PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer; sent++;//PICMP - ��������� �� ICMP
      if (result != 0)//���� ����� �������

      {
         struct in_addr ReplyAddr;//��� ������ ������

         ReplyAddr.S_un.S_addr = pEchoReply->Address; cout//replyaddr ����������� � �������� ���
            << "����� �� "

            << inet_ntoa(ReplyAddr)//������� � ������� �������
            << ": ����� ����=3" << ReplySize
            << " �����=" << pEchoReply->RoundTripTime

            << "��"
            << " TTL=" << (int)TTL
            << endl;

         received++;

         if (pEchoReply->RoundTripTime < min)
            min = pEchoReply->RoundTripTime;
         if (pEchoReply->RoundTripTime > max)

            max = pEchoReply->RoundTripTime;

         average += pEchoReply->RoundTripTime;

      }
      else
         cout << "������! ������: " << pEchoReply->Status << endl;

   }

   delete[] ReplyBuffer;

   delete[] buffer;

   cout << endl;
   cout

      << "���������� Ping ��� " << host << ":\n" << "\t�������: ���������� = " << sent
      << ","
      << "�������� = " << received << ", " << "�������� = "

      << sent - received << endl;
   cout
      << "��������������� ����� ������-�������� � ��:\n"

      << "\n����������� = " << min << " ����, "
      << "������������ = " << max << " ����, "
      << "������� = " << average / requestCount << " ����" << endl << endl;
}