#include "memory.h"
#include "stdio.h"
#include "sys/socket.h"
#include "netinet/in.h"
#include "arpa/inet.h"
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

struct VoilenceAtTheDisco
{
  int myAddr[2];
  int friendAddr[2];
};


void *SenderFunc(void *args)
{
  struct VoilenceAtTheDisco portAdresses = *(struct VoilenceAtTheDisco *)args;
  int myAddr = portAdresses.myAddr[0];
  int friendAddr = portAdresses.friendAddr[0];
  int socketDesc;
  if((socketDesc = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    printf("Bad!\n");
    return 0;
  }
  printf("%d\n", socketDesc);

  struct sockaddr_in myAddress;
  memset(&myAddress, 0, sizeof(myAddress));
  myAddress.sin_family = AF_INET;
  myAddress.sin_port = htons(myAddr);
  if(!inet_aton("127.0.0.1", &(myAddress.sin_addr)))
    printf("Worse\n");

  if(bind(socketDesc, (struct sockaddr *)&myAddress, sizeof(myAddress)) < 0)
  {
    printf("Bind err\n");
    return 0;
  }

  struct sockaddr_in destAddress;
  memset(&destAddress, 0, sizeof(destAddress));
  destAddress.sin_family = AF_INET;
  destAddress.sin_port = htons(friendAddr);
  if(!inet_aton("127.0.0.1", &(destAddress.sin_addr)))
    printf("Worse\n");

  int flag = 0;
  while(flag == 0)
  {
    char message[1024];
    gets(message);
    if(sendto(socketDesc, message, strlen(message) + 1, 0, (struct sockaddr *)&destAddress, sizeof(destAddress)) < 0)
    {
      printf("Send error\n");
      return 0;
    }
    if(strcmp(message, ":q") == 0)
    {
      flag = 1;
      exit(0);
    }
  }
}

void *RecieverFunc(void *args)
{
  struct VoilenceAtTheDisco portAdresses = *(struct VoilenceAtTheDisco *)args;
  int myAddr = portAdresses.myAddr[1];
  int friendAddr = portAdresses.friendAddr[1];
  int socketDesc;
  if((socketDesc = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
  {
    printf("Bad!\n");
    return 0;
  }
  printf("%d\n", socketDesc);

  struct sockaddr_in myAddress;
  memset(&myAddress, 0, sizeof(myAddress));
  myAddress.sin_family = AF_INET;
  myAddress.sin_port = htons(myAddr);
  if(!inet_aton("127.0.0.1", &(myAddress.sin_addr)))
    printf("Worse\n");

  if(bind(socketDesc, (struct sockaddr *)&myAddress, sizeof(myAddress)) < 0)
  {
    printf("Bind err\n");
    return 0;
  }

  int flag = 0;
  char message[1024];
  while(flag == 0)
  {
    if(recvfrom(socketDesc, message, sizeof(message), 0, 0, 0) < 0)
    {
      printf("Send error\n");
      return 0;
    }
    if(strcmp(message, ":q") == 0)
    {
      printf("\nUser %d offline\n", friendAddr);
      flag = 1;
      exit(0);
    }
    else
    {
      printf("#%d: %s\n", friendAddr, message);
    }
  }
}



int main(int argc, char **argv)
{
  struct VoilenceAtTheDisco portAdresses;
  switch (argc)
  {
    case 2:
      if(strcmp(argv[1], "a"))
      {
        portAdresses.myAddr[0] = 51101;
        portAdresses.myAddr[1] = 51102;
        portAdresses.friendAddr[0] = 51104;
        portAdresses.friendAddr[1] = 2;
      }
      else if(strcmp(argv[1], "b"))
      {
        portAdresses.myAddr[0] = 51103;
        portAdresses.myAddr[1] = 51104;
        portAdresses.friendAddr[0] = 51102;
        portAdresses.friendAddr[1] = 1;
      }
      else
      {
        printf("Wrong argument, should be either 'a', or 'b'\n");
        exit(0);
      }
    break;

    default:
      printf("Wrong nuber of arguments\n");
      exit(0);
    break;
  }

  printf("Enjoy your chat!\n");
  pthread_t threadIds[2];

  pthread_create(&threadIds[0], 0, SenderFunc, &portAdresses);
  pthread_create(&threadIds[1], 0, RecieverFunc, &portAdresses);
  pthread_join(threadIds[0], 0);
  pthread_join(threadIds[1], 0);

  return 0;
}
