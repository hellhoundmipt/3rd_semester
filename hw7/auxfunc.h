#include <sys/types.h>

struct MsqInit
{
  long type;
  pid_t pid;
};

struct Message
{
  long type;
  char msg[1024];
};

struct ChatInfo
{
  pid_t myPid;
  pid_t companionPid;
  int msqId;
};

int ParsArgs(int argsCount, char **args)
{
  if((strcmp(args[1], "-h") == 0)  || (strcmp(args[1], "--help") == 0))
  {
    return 1;
  }
  if((strcmp(args[1], "-rm") == 0)  || (strcmp(args[1], "--remove") == 0))
  {
    return 2;
  }
  if((strcmp(args[1], "1") == 0)  || (strcmp(args[1], "2") == 0))
  {
    return 3;
  }
  return -1;
}
