#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include "auxfunc.h"
#include <unistd.h>
#include <string.h>

int LaunchClient(int msqId);
int LaunchServer(int msqId);
void RemoveMsgQ(int msqId);

int main(int argsCount, char **args)
{
  key_t key = ftok("key", 0);
  printf("key = %d\n", key);
  int msqId = msgget(key, IPC_CREAT | 0666);
  printf("msqId = %d\n", msqId);
  int instr = ParsArgs(argsCount, args);
  switch (instr)
  {
    case -1:
      printf("Wrong arguments\n");
      break;

    case 1:
      printf("HELP\n-h\t--help\t\t\tShow help\n");
      printf("-c\t--client\t\tLaumching client\n");
      printf("-s\t--server\t\tLaumching server\n");
      printf("-rm\t--remove\t\tRemove message queue\n");
      printf(":q (during chat)\t\tStop chat\n");
      break;

    case 2:
    printf("Launching client\n");
      LaunchClient(msqId);
      break;

    case 3:
    printf("Launching server\n");
      LaunchServer(msqId);
      break;

    case 4:
      RemoveMsgQ(msqId);
      break;
  }
  return 0;
}

int LaunchClient(int msqId)
{
  struct Msg2Serv sender;
  struct Msg2Client reciever;
  sender.type = 1;
  int senderSize = sizeof(struct Msg2Serv) - sizeof(long);
  int recieverSize = sizeof(struct Msg2Client) - sizeof(long);
  sender.pid = getpid();
  while(1)
  {
    printf("Enter message\n");
    gets(sender.msg);
    msgsnd(msqId, &sender, senderSize, 0);
    if(strcmp(sender.msg, ":q") == 0)
    {
      printf("Client out\n");
      return 0;
    }

    msgrcv(msqId, &reciever, recieverSize, sender.pid, 0);
    if(strcmp(reciever.msg, ":q") == 0)
    {
      printf("Server out\n");
      return 0;
    }
    printf("S: %s\n", reciever.msg);
  }
}


int LaunchServer(int msqId)
{
  struct Msg2Serv reciever;
  struct Msg2Client sender;
  int recieverSize = sizeof(struct Msg2Serv) - sizeof(long);
  int senderSize = sizeof(struct Msg2Client) - sizeof(long);
  while(1)
  {
    msgrcv(msqId, &reciever, recieverSize, 1, 0);
    if(strcmp(reciever.msg, ":q") == 0)
    {
      printf("Client out\n");
      return 0;
    }
    printf("C: %s\n", reciever.msg);

    sender.type = reciever.pid;

    printf("Enter message\n");
    gets(sender.msg);
    msgsnd(msqId, &sender, senderSize, 0);
    if(strcmp(sender.msg, ":q") == 0)
    {
      printf("Server out\n");
      return 0;
    }
  }
}

void RemoveMsgQ(int msqId)
{
  if(msgctl(msqId, IPC_RMID, 0) == 0)
  {
    printf("Message queue removed successfully\n");
  }
  else
  {
    printf("Oooooops, trouble deleting message queue\n");
  }
}
