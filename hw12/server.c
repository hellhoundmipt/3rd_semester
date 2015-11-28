#include <pthread.h>
#include "memory.h"
#include "stdio.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "auxfile.h"

#define maxClients 10

struct ClientsList
{
  int clientSockDesc;
  char name[28];
};


void *ServeClient(void *args)
{
  struct ClientsList clients = *(struct ClientsList *)args;
  int exitFlag = 0;
  while(exitFlag == 0)
  {
    char message[messageLength];
    read(clients.clientSockDesc, message, sizeof(message));
    printf("%s\n", message);
    if(strcmp(message, ":q") == 0)
    {
      close(clients.clientSockDesc);
      printf("[%s] offline\n", clients.name);
      return NULL;
    }
    write(clients.clientSockDesc, message, sizeof(message));
    printf("Letter thrown!\n");
  }
}


int SearchForName(char *name, struct ClientsList *clients, int clientsCount)
{
  int i;
  for(i = 0; i < clientsCount; i++)
  {
    if(strcmp(name, clients[i].name) == 0)
      return 1;
  }
  return 0;
}


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

  struct ClientsList clients[maxClients];
  int clientsCount = 0;
  pthread_t threadIds[10];
  while(1)
  {
    listen(passiveSockDesc, 10);
    clients[clientsCount].clientSockDesc = accept(passiveSockDesc, 0, 0);

    char name[28];
    read(clients[clientsCount].clientSockDesc, name, sizeof(name));
    if(SearchForName(name, clients, clientsCount) == 1)
    {
      printf("Access denied, name already in use.\n");
      close(clients[clientsCount].clientSockDesc);
    }
    else
    {
      strcpy(clients[clientsCount].name, name);
      printf("[%s] connected, descriptor: %d\n", clients[clientsCount].name, clients[clientsCount].clientSockDesc);
      write(clients[clientsCount].clientSockDesc, acceptLetter, strlen(acceptLetter) + 1);

      pthread_create(&threadIds[0], 0, ServeClient, &clients[clientsCount]);
      clientsCount++;
    }
  }

  close(passiveSockDesc);
  return 0;
}
