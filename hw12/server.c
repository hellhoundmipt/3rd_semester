#include <pthread.h>
#include <stdlib.h>
#include <sys/types.h>
#include "memory.h"
#include "stdio.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "auxfile.h"

#define maxClients 10
int clientsCount = 0;

struct ClientsList
{
  int clientSockDesc;
  int numOfClient;
  char name[28];
} clients[maxClients];

void *ServeClient(void *args);
void SendToAll(char *message, int numOfClient);
void SendClientsList(int numOfClient);
char *MakeMessage(char *message, char* name);
int ApplyClient(char *name);
int PlaceClient(char* name, int clientSockDesc);
void ClearClient(int numOfClient);;
int ParsMessage(char *message);


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

  int i = 0;
  for(i; i < maxClients; i++)
  {
    clients[i].numOfClient = -1;
  }

  while(1)
  {
    listen(passiveSockDesc, 10);
    int clientSockDesc = accept(passiveSockDesc, 0, 0);

    char name[28];
    read(clientSockDesc, name, sizeof(name));
    if(ApplyClient(name) == 1)
    {
      printf("Access denied, name already in use or server is full.\n");
      close(clientSockDesc);
    }
    else
    {
      int data = PlaceClient(name, clientSockDesc);
      pthread_t dummy;
      pthread_create(&dummy, NULL, ServeClient, &data);
    }
  }

  close(passiveSockDesc);
  return 0;
}


void *ServeClient(void *args)
{
  int numOfClient = *(int *)args;
  int exitFlag = 0;
  while(exitFlag == 0)
  {
    char message[messageLength];
    read(clients[numOfClient].clientSockDesc, message, sizeof(message));
    printf("In service3\n");
    printf("%s\n", message);
    int switchVar = ParsMessage(message);
    switch (switchVar)
    {
      case 0:
        SendToAll(message, clients[numOfClient].numOfClient);
        printf("Letter thrown!\n");
      break;

      case 1:
        close(clients[numOfClient].clientSockDesc);
        printf("[%s] /:offline:/\n", clients[numOfClient].name);
        SendToAll("/:offline:/", clients[numOfClient].numOfClient);
        ClearClient(clients[numOfClient].numOfClient);
        return NULL;
      break;

      case 2:
        SendClientsList(numOfClient);
      break;
    }
    int i = 0;
    for(i; i < maxClients; i++)
    {
      printf("%s: %d: %d\t", clients[i].name, clients[i].clientSockDesc, clients[i].numOfClient);
    }
    printf("\n");
  }
}


void SendToAll(char *message, int numOfClient)
{
  message = MakeMessage(message, clients[numOfClient].name);
  int i = 0;
  for(i; i < maxClients; i++)
  {
    if((i != numOfClient) && (clients[i].numOfClient != -1))
      write(clients[i].clientSockDesc, message, strlen(message) + 1);
  }
}

void SendClientsList(int numOfClient)
{
  int i = 0;
  char *message = calloc(messageLength, sizeof(char));
  for(i; i < maxClients; i++)
  {
    if(clients[i].numOfClient != -1)
    {
      message = MakeMessage("/:online:/", clients[i].name);
      write(clients[numOfClient].clientSockDesc, message, strlen(message) + 1);
    }
  }
}

char *MakeMessage(char *message, char* name)
{
  char returnMessage[messageLength];
  strcpy(returnMessage, "[");
  strcat(returnMessage, name);
  strcat(returnMessage, "] ");
  strcat(returnMessage, message);
  return returnMessage;
}

int ApplyClient(char *name)
{
  int i;
  if(clientsCount >= maxClients)
    return 1;
  for(i = 0; i < maxClients; i++)
  {
    if(strcmp(name, clients[i].name) == 0)
      return 1;
  }
  return 0;
}

int PlaceClient(char* name, int clientSockDesc)
{
  int i = 0;
  for(i; i <= maxClients; i++)
  {
    if(clients[i].numOfClient == -1)
    {
      strcpy(clients[i].name, name);
      clients[i].clientSockDesc = clientSockDesc;
      clients[i].numOfClient = i;
      write(clients[i].clientSockDesc, acceptLetter, strlen(acceptLetter) + 1);
      printf("[%s] connected, descriptor: %d\n", clients[i].name, clients[i].clientSockDesc);
      SendToAll("/:online:/", i);
      printf("%s: %d: %d: %d\n", clients[i].name, clients[i].clientSockDesc, clients[i].numOfClient, i);
      clientsCount++;
      return i;
    }
  }
}

void ClearClient(int numOfClient)
{
  clients[numOfClient].numOfClient = -1;
  bzero(clients[numOfClient].name, strlen(clients[numOfClient].name) + 1);
}

int ParsMessage(char *message)
{
  if(strcmp(message, ":q") == 0)
    return 1;
  if(strcmp(message, ":n") == 0)
    return 2;
  return 0;
}
