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
#include <errno.h>

/*#define myAddr 51101
#define friendAddr 51102*/

void *SenderFunc(void *args)
{
  int myAddr = 51103;
  int friendAddr = 51102;
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


  int reuse;
  if (setsockopt(socketDesc, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(int)) == -1)
  {
   printf("Reuse port Error : %s\n", strerror(errno));
  }

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
  int myAddr = 51104;
  int friendAddr = 1;
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


int main()
{
  printf("Enjoy your chat!\n");
  pthread_t threadIds[2];

  pthread_create(&threadIds[0], 0, SenderFunc, NULL);
  pthread_create(&threadIds[1], 0, RecieverFunc, NULL);
  pthread_join(threadIds[0], 0);
  pthread_join(threadIds[1], 0);
  return 0;
}
