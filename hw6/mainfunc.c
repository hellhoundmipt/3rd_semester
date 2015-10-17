#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "auxfunc.h"

#define threadsCount 2

int ParsArgs(int argsCount, char **args)
{
  switch (argsCount)
  {
    case 2:
      if((strcmp(args[1], "-i") == 0)  || (strcmp(args[1], "--init") == 0))
      {
        return 0;
      }
      if((strcmp(args[1], "-h") == 0)  || (strcmp(args[1], "--help") == 0))
      {
        return 1;
      }
      if((strcmp(args[1], "-c") == 0)  || (strcmp(args[1], "--calculate") == 0))
      {
        return 2;
      }
      if((strcmp(args[1], "-rd") == 0)  || (strcmp(args[1], "--read") == 0))
      {
        return 3;
      }
      if((strcmp(args[1], "-rm") == 0)  || (strcmp(args[1], "--remove") == 0))
      {
        return 4;
      }
      break;
  }
  return -1;
}


int main(int argsCount, char **args)
{
  int instr = ParsArgs(argsCount, args);
  switch (instr)
  {
    case -1:
      printf("Wrong arguments\n");
      break;

    case 0:
      InitVIPC();
      break;

    case 1:
      printf("HELP\n-h\t--help\t\t\tShow help\n");
      printf("-i\t--init\t\t\tInitialize shmem and semaphore\n");
      printf("-c\t--calculate\t\tLaunch calculation\n");
      printf("-rd\t--read\t\t\tDisplay Pi\n");
      printf("-rm\t--remove\t\tRemove shmem and semaphore\n");
      break;

    case 2:
      printf("Launching calculation of Pi in %d threads\n", threadsCount);
      Calculate();
      break;

    case 3:
      ReadPi();
      break;

    case 4:
      RmVIPC();
      break;
  }
  return 0;
}
