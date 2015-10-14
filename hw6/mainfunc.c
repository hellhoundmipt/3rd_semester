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

struct ParsRes
{
  int instr;
  int calcTime;
};

struct ParsRes ParsArgs(int argsCount, char **args)
{
  struct ParsRes res;
  switch (argsCount)
  {
    case 2:
      if((strcmp(args[1], "-h") == 0)  || (strcmp(args[1], "--help") == 0))
      {
        res.instr = 1;
        return res;
      }
      break;

    case 3:
      if((strcmp(args[1], "-ot") == 0)  || (strcmp(args[1], "--onethread") == 0))
      {
        res.instr = 2;
        res.calcTime = atoi(args[2]);
        return res;
      }
      if((strcmp(args[1], "-mt") == 0)  || (strcmp(args[1], "--multithread") == 0))
      {
        res.instr = 3;
        res.calcTime = atoi(args[2]);
        return res;
      }
      break;
  }
  res.instr = -1;
  return res;
}

void OneThread(int exTime)
{
  double x, y;
  int yesCounter = 0, noCounter = 0;
  clock_t start, endTime;
  start = clock() / CLOCKS_PER_SEC;

  while((clock() / CLOCKS_PER_SEC) - start < exTime)
  {
    x = -1.0f + 2.0f * drand48();
    y = -1.0f + 2.0f * drand48();
    if (x*x + y*y <= 1)
      yesCounter++;
    else
      noCounter++;
  }
  printf("%d\t%d\n", yesCounter, noCounter);
  double pi = 4 * (float)yesCounter / (float)(yesCounter + noCounter);
  printf("Pi = %f\n", pi);
  FILE *resfile = fopen("Database.txt", "a");
  fprintf(resfile, "1 thread pi = %f\tyesCounter = %d\tnoCounter = %d\texpected time = %d\n\n", pi, yesCounter, noCounter, exTime);
  fclose(resfile);
}


int main(int argsCount, char **args)
{
  struct ParsRes res = ParsArgs(argsCount, args);
  switch (res.instr)
  {
    case -1:
      printf("Wrong arguments\n");
      break;

    case 1:
      printf("HELP\n-h\t--help\t\t\t\t\tShow help\n");
      printf("-ot\t--onethread\t[prefered time]\t\tLaunch calculation in 1 thread\n");
      printf("-mt\t--multithread\t[prefered time]\t\tLaunch calculation in %d threads\n", threadsCount);
      break;

    case 2:
      printf("Launching calculation of Pi in one thread\n");
      OneThread(res.calcTime);
      break;

    case 3:
      printf("Launching calculation of Pi in %d threads\n", threadsCount);
      MultiThread(res.calcTime);
      break;
  }
  return 0;
}
