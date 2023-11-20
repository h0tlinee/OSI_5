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

   hostent* host_entity = gethostbyname(hostname.c_str()); if (host_entity == nullptr)//host_ent - для хранения информации об узле
      return false;

   in_addr* addr = (in_addr*)(host_entity->h_addr_list[0]); //получаем адрес в in_addr из hostent
   host = inet_ntoa(*addr);//в host запишем "очеловеченный" адрес
   inet_pton(AF_INET, host.c_str(), &ipaddr);//в ipaddr запишем двоичное представление host
   

}

void MakeRequest(IPAddr ipaddr, string& host)//запрос к адресу

{
   SetConsoleCP(1251);
   SetConsoleOutputCP(1251);

   int min = 1000, average = 0, max = 0, sent = 0, received = 0; char* buffer = new char[BufferSize];

   for (int i = 0; i < BufferSize; i++)//заполняем буфер данными
      buffer[i] = rand();
   HANDLE hIcmpFile = IcmpCreateFile();//открывает дескриптор на который можно делать эхо-запросы ipv4

   int ReplySize = sizeof(ICMP_ECHO_REPLY) + BufferSize; char* ReplyBuffer = new char[ReplySize];//размер ответа и буфер ответа
   for (int i = 0; i < requestCount; ++i)

   {

      int result = IcmpSendEcho(hIcmpFile, ipaddr, buffer, BufferSize, NULL, ReplyBuffer, ReplySize, 1000);//время - 1000

      PICMP_ECHO_REPLY pEchoReply = (PICMP_ECHO_REPLY)ReplyBuffer; sent++;//PICMP - указатель на ICMP
      if (result != 0)//если ответ получен

      {
         struct in_addr ReplyAddr;//для адреса ответа

         ReplyAddr.S_un.S_addr = pEchoReply->Address; cout//replyaddr преобразуем в двоичный тип
            << "Ответ от "

            << inet_ntoa(ReplyAddr)//выводим в обычном формате
            << ": число байт=3" << ReplySize
            << " время=" << pEchoReply->RoundTripTime

            << "мс"
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
         cout << "ОШИБКА! Статус: " << pEchoReply->Status << endl;

   }

   delete[] ReplyBuffer;

   delete[] buffer;

   cout << endl;
   cout

      << "Статистика Ping для " << host << ":\n" << "\tПакетов: отправлено = " << sent
      << ","
      << "получено = " << received << ", " << "потеряно = "

      << sent - received << endl;
   cout
      << "Приблизительное время приема-передачи в мс:\n"

      << "\nМинимальное = " << min << " мсек, "
      << "Максимальное = " << max << " мсек, "
      << "Среднее = " << average / requestCount << " мсек" << endl << endl;
}