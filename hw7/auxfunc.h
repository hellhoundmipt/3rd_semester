#include <sys/types.h>

struct Msg2Serv
{
  long type;
  pid_t pid;
  char msg[1024];
};

struct Msg2Client
{
  long type;
  char msg[1024];
};

int ParsArgs(int argsCount, char **args)
{
  if((strcmp(args[1], "-h") == 0)  || (strcmp(args[1], "--help") == 0))
  {
    return 1;
  }
  if((strcmp(args[1], "-c") == 0)  || (strcmp(args[1], "--client") == 0))
  {
    return 2;
  }
  if((strcmp(args[1], "-s") == 0)  || (strcmp(args[1], "--server") == 0))
  {
    return 3;
  }
  if((strcmp(args[1], "-rm") == 0)  || (strcmp(args[1], "--remove") == 0))
  {
    return 4;
  }
  return -1;
}
