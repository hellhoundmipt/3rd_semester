#include <stdio.h>
#include <string.h>
#include <stdbool.h>

char *helpMessage = "Keys:\n-h\t\t\tshow help\n-k [keyfile]\t\tset keyfile for shared memory\n-i or [inputfile]\tset input file\n-g or [shmemory]\t\tread from shared memory\n-r [shmemory]\tremove shared memory\n-cheese\t\t\t\t...\n";
char *restrictMessage = "Do NOT delete SHMEM_INFO, it will be removed automatically when you clear shared memory with -r or --remove key\n";

struct ParsRes ParsArgs(int argsCount, char **args, struct Base *argsMain, int argsMainCount)
{
  bool generalFlag = false;
  int i;
  for(i = 0; i < argsMainCount; i++)
  {
    int j;
    
  }
}
