#include <pthread.h>
#include "memory.h"
#include "stdio.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "auxfile.h"

void *ServeClient(void *args);

struct ClientsList
{
  int clientSockDesc;
  char name[28];
};

int main(int argc, char const *argv[])
{
  printf("Server!\n");
  int passiveSockDesc = socket(AF_INET, SOCK_STREAM, 0);
  printf("Desc = %d\n", passiveSockDesc);

  struct sockaddr_in myAddress;
  memset(&myAddress, 0, sizeof(myAddress));
  myAddress.sin_family = AF_INET;
  myAddress.sin_port = htons(51101);      //port > 49000
  if(!inet_aton("127.0.0.1", &(myAddress.sin_addr)))
    printf("Worse\n");

  if(bind(passiveSockDesc, (struct sockaddr *)&myAddress, sizeof(myAddress)) < 0)
  {
    printf("Bind err\n");
    return 0;
  }

  struct ClientsList clients;
  pthread_t threadIds[10];
  while(1)
  {
    listen(passiveSockDesc, 10);      //10 - размер очереди
    //while(1) - для большого кол-ва клиентов
    clients.clientSockDesc = accept(passiveSockDesc, 0, 0);

    read(clients.clientSockDesc, clients.name, sizeof(clients.name));
    printf("[%s] connected, descriptor: %d\n", clients.name, clients.clientSockDesc);
    write(clients.clientSockDesc, acceptLetter, strlen(acceptLetter) + 1);

    pthread_create(&threadIds[0], 0, ServeClient, &clients);
  }

  close(clients.clientSockDesc);
  close(passiveSockDesc);
  return 0;
}

void *ServeClient(void *args)
{
  struct ClientsList clients = *(struct ClientsList *)args;
  int exitFlag = 0;
  while(exitFlag == 0)
  {
    char message[messageLength];
    read(clients.clientSockDesc, message, sizeof(message));
    printf("%s\n", message);
    write(clients.clientSockDesc, message, sizeof(message));
    printf("Letter thrown!\n");
  }
  printf("Hi, man!\n");
}
