#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define threadsCount 2

struct Main2ThrMain
{
  int shmId;
  int semId;
};

void Add(int semId, int value)
{
  struct sembuf myBuf;
  myBuf.sem_op = value;
  myBuf.sem_num = 0;
  myBuf.sem_flg = 0;
  semop(semId, &myBuf, 1);
}

void Sub(int semId, int value)
{
  struct sembuf myBuf;
  myBuf.sem_op = -value;
  myBuf.sem_num = 0;
  myBuf.sem_flg = 0;
  semop(semId, &myBuf, 1);
}

void *ThreadMain(void *args)
{
  struct Main2ThrMain transmData = *(struct Main2ThrMain*)args;

  int *data = shmat(transmData.shmId, 0, 0);
  double x, y;
  int i;
  long int yesCounter, noCounter;
  long int seedval;
  struct drand48_data *buffer = calloc(1, sizeof(struct drand48_data));
  srand48_r(seedval, buffer);
  while(1 < 2)
  {
    yesCounter = 0;
    noCounter = 0;
    for(i = 0; i < 10000; i++)
    {
      drand48_r(buffer, &x);
      drand48_r(buffer, &y);
      x = -1.0f + 2.0f * x;
      y = -1.0f + 2.0f * y;
      if (x*x + y*y <= 1)
        yesCounter++;
      else
        noCounter++;
    }
    Sub(transmData.semId, 1);
    data[0] = data[0] + yesCounter;
    data[1] = data[1] + noCounter;
    Add(transmData.semId, 1);
  }
}

void Calculate()
{
  int i;
  struct Main2ThrMain transmData;
  key_t key = ftok("key", 0);
  printf("key = %d\n", key);
  transmData.semId = semget(key, 1, IPC_CREAT | 0666);
  printf("semId = %d\n", transmData.semId);
  transmData.shmId = shmget(key, 2*sizeof(double), IPC_CREAT | 0777);
  printf("shmId = %d\n", transmData.shmId);

  pthread_t threadIndex[threadsCount];
  for(i = 0; i < threadsCount; i++)
  {
    threadIndex[i] = i;
    pthread_create(&(threadIndex[i]), 0, ThreadMain, &transmData);
  }
  for(i = 0; i < threadsCount; i++)
  {
    pthread_join(threadIndex[i], 0);
  }
}


void ReadPi()
{
  key_t key = ftok("key", 0);
  printf("key = %d\n", key);
  int shmId = shmget(key, 2*sizeof(long int), IPC_CREAT | 0777);
  printf("shmId = %d\n", shmId);

  int *data = shmat(shmId, 0, 0);
  long int yesCounter = data[0];
  long int noCounter = data[1];
  printf("%ld\t%ld\n", yesCounter, noCounter);
  double pi = 4 * (double)yesCounter / (double)(yesCounter + noCounter);
  printf("Pi = %lf\n", pi);
}

void RmVIPC()
{
  key_t key = ftok("key", 0);
  printf("key = %d\n", key);
  int semId = semget(key, 1, IPC_CREAT | 0666);
  printf("semId = %d\n", semId);
  int shmId = shmget(key, 2*sizeof(double), IPC_CREAT | 0777);
  printf("shmId = %d\n", shmId);

  semctl(semId, IPC_RMID, 0);
  shmctl(shmId, IPC_RMID, 0);
  printf("VIPC successfully removed!\n");
}

void InitVIPC()
{
  key_t key = ftok("key", 0);
  printf("key = %d\n", key);
  int semId = semget(key, 1, IPC_CREAT | 0666);
  printf("semId = %d\n", semId);
  int shmId = shmget(key, 2*sizeof(double), IPC_CREAT | 0777);
  printf("shmId = %d\n", shmId);

  Add(semId, 1);

  int *data = shmat(shmId, 0, 0);
  data[0] = 0;
  data[1] = 0;
  printf("VIPC initialized!\n");
}
