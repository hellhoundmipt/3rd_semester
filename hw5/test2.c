#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main()
{
  int sizeOfFile = 1000, result;
  FILE * aux_fileDesc = fopen("SHMEM_INFO", "wt");
  fprintf(aux_fileDesc, "%d\n", sizeOfFile);
  fclose(aux_fileDesc);

  aux_fileDesc = fopen("SHMEM_INFO", "rt");
  fscanf(aux_fileDesc, "%d", &result);
  fclose(aux_fileDesc);
  printf("%d\n", result);
}
