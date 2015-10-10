//My Project

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "functions.h"

int main (int argsCount, char **args)
{
  int error = 0;
  switch (argsCount)
  {
    case 2:
      error = Case2Args(args[1]);
      break;

    case 3:
      error = case3Args(args);
      break;

    case 5:
      error = Case5Args(args);
      break;

    default:
      printf("Wrong number of arguments\n");
      exit(1);
      break;
  }

  switch (error)
  {
    case 1:
      printf("Not appropriate key\n");
      break;
    case 2:
      printf("Input file and key file must be different files\n");
      break;
    case 3:
      printf("No appropriate file in the directory\n");
      break;
    case 4:
      printf("Cannot get key\n");
      break;
  }
}
