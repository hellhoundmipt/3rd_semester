#include <pthread.h>
#include "memory.h"
#include "stdio.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include "stdlib.h"
#include "auxfile.h"

const char confirmationLetter[] = "Name is free, connection accepted";

struct Data
{
  int socketDesc;
  char myName[28];
};

void *SenderFunc(void *args);
void *RecieverFunc(void *args);

int main()
{
  printf("Client\n");
  struct Data data;
  data.socketDesc = socket(AF_INET, SOCK_STREAM, 0);
  printf("Desc: %d\n", data.socketDesc);

  struct sockaddr_in serverAddress;
  memset(&serverAddress, 0, sizeof(serverAddress));
  serverAddress.sin_family = AF_INET;
  serverAddress.sin_port = htons(51101);      //port > 49000
  if(!inet_aton("127.0.0.1", &(serverAddress.sin_addr)))
    printf("Worse\n");

  int connectRes = connect(data.socketDesc, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
  printf("Connect res %d\n", connectRes);
  if(connectRes < 0)
    exit(0);
  printf("Enter your name:\n");
  scanf("%s", data.myName);
  write(data.socketDesc, data.myName, strlen(data.myName) + 1);

  char buffer[128];
  read(data.socketDesc, buffer, sizeof(buffer));
  if(strcmp(buffer, acceptLetter) == 0)
  {
    printf("%s\n", confirmationLetter);
  }
  else
  {
    printf("Access denied: server full or name if unaviliable\n");
    exit(0);
  }
  printf("Instructions:\n");
  printf("\tpress :q to quit the chat\n");
  printf("\tpress :n to show people offline\n");
  printf("\trespect chicken because she has lost control again...\n");

  pthread_t threadIds[2];
  pthread_create(&threadIds[0], 0, SenderFunc, &data);
  pthread_create(&threadIds[1], 0, RecieverFunc, &data);
  pthread_join(threadIds[0], 0);
  pthread_join(threadIds[1], 0);

  return 0;
}

void *SenderFunc(void *args)
{
  struct Data data = *(struct Data *)args;
  while(1)
  {
    char message[messageLength];
    gets(message);
    write(data.socketDesc, message, strlen(message) + 1);
    if(strcmp(message, ":q") == 0)
    {
      close(data.socketDesc);
      printf("Rock the microphone!\n");
      exit(0);
    }
  }
}

void *RecieverFunc(void *args)
{
  struct Data data = *(struct Data *)args;
  while(1)
  {
    char message[messageLength];
    read(data.socketDesc, message, sizeof(message));
    printf("%s\n", message);
  }
}
