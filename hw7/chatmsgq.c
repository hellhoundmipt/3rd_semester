#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include "auxfunc.h"
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void LaunchChat(int msqId);
void RemoveMsq();
void *SenderFunc(void *args);
void *RecieverFunc(void *args);
struct ChatInfo InitFunc(int status, int msqId);

pthread_t threadIds[2];

int main(int argsCount, char **args)
{

  int instr = ParsArgs(argsCount, args);
  switch (instr)
  {
    case -1:
      printf("Wrong arguments\n");
      break;

    case 1:
      printf("HELP\n-h\t--help\t\t\tShow help\n");
      printf("-rm\t--remove\t\tRemove message queue\n");
      printf("1 or 2\t\t\t\tStart chat (each companon should use different number)\n");
      printf(":q (during chat)\t\tStop chat\n");
      break;

    case 2:
      RemoveMsq();
      break;

    case 3:
      printf("Enjoy your chat!\n");
      int status = atoi(args[1]);
      LaunchChat(status);
  }
  return 0;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void LaunchChat(int status)
{
  key_t key = ftok("key", 0);
  printf("key = %d\n", key);
  int msqId = msgget(key, IPC_CREAT | 0666);
  printf("msqId = %d\n", msqId);

  struct ChatInfo info = InitFunc(status, msqId);
  info.msqId = msqId;
  pthread_create(&threadIds[0], 0, SenderFunc, &info);
  pthread_create(&threadIds[1], 0, RecieverFunc, &info);
  pthread_join(threadIds[0], 0);
  pthread_join(threadIds[1], 0);
}

struct ChatInfo InitFunc(int status, int msqId)
{
  int initSize = sizeof(struct MsqInit) - sizeof(long);
  struct MsqInit init;
  struct ChatInfo info;

  switch (status)
  {
    case 1:
      init.type = 1;
      init.pid = getpid();
      info.myPid = init.pid;
      msgsnd(msqId, &init, initSize, 0);
      msgrcv(msqId, &init, initSize, info.myPid, 0);
      info.companionPid = init.pid;
      break;

    case 2:
      msgrcv(msqId, &init, initSize, 1, 0);
      info.companionPid = init.pid;
      init.type = init.pid;
      init.pid = getpid();
      info.myPid = init.pid;
      msgsnd(msqId, &init, initSize, 0);
      break;
  }
  return info;
}


void *SenderFunc(void *args)
{
  struct ChatInfo info = *(struct ChatInfo*)args;
  struct Message message;
  message.type = info.companionPid;
  int size = sizeof(struct Message) - sizeof(long);
  int flag = 0;
  printf("In sender");
  while(flag == 0)
  {
    printf("You: ");
    gets(message.msg);
    msgsnd(info.msqId, &message, size, 0);
    if(strcmp(message.msg, ":q") == 0)
    {
      flag = 1;
    }
  }
}

void *RecieverFunc(void *args)
{
  struct ChatInfo info = *(struct ChatInfo*)args;
  struct Message message;
  int size = sizeof(struct Message) - sizeof(long);
  int flag = 0;
  printf("In reciever");
  while(flag == 0)
  {
    gets(message.msg);
    msgrcv(info.msqId, &message, info.myPid,size, 0);
    if(strcmp(message.msg, ":q") == 0)
    {
      printf("User %d out\n", info.companionPid);
      flag = 1;
    }
    else
    {
      printf("%d: %s\n", info.companionPid, message.msg);
    }
  }
}

void RemoveMsq()
{
  key_t key = ftok("key", 0);
  printf("key = %d\n", key);
  int msqId = msgget(key, IPC_CREAT | 0666);
  printf("msqId = %d\n", msqId);

  if(msgctl(msqId, IPC_RMID, 0) == 0)
  {
    printf("Message queue removed successfully\n");
  }
  else
  {
    printf("Oooooops, trouble deleting message queue\n");
  }
}
