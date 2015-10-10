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
  key_t key = ftok("dummy2", 0);
  printf("key = %d\n", key);

  int shmId = shmget(key, 4, IPC_CREAT | 0666);
	int shmId2 = shmget(key, 4, IPC_CREAT | 0666);
  printf("shmId: %d\n", shmId);

  int *data1 = shmat(shmId, 0, 0);
	int *data2 = shmat(shmId2, 0, 0);
	*data1 = 1;
	*data2 = 3;
  return 0;
}
