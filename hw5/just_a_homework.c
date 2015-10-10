#include <stdio.h>
#include <sys/ipc.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>

int main (int argsCount, char **args)
{
  key_t key = ftok("key", 0);
  printf("key = %d\n", key);

  int shmId = shmget(key, proglength, IPC_CREAT | 0777);
  printf("shmId: %d\n", shmId);

  char *data = shmat(shmId, 0, 0);
  int fileDesc = open(args[1], O_RDONLY);
	if(fileDesc < 0)
	{
		printf("No appropriate file in the directory\n");
    exit(-1);
	}
	printf("Opened file %s\n", args[1]);
	close(fileDesc);
  char string[proglength];
}
