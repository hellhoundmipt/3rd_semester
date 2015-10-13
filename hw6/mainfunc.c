#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define threadsCount 10

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
  printf("2\n");
  struct Main2ThrMain transmData = *(struct Main2ThrMain*)args;
  int *data = shmat(transmData.shmId, 0, 0);
  int i;
  double x, y;
  int yesCounter;
  int noCounter;
  while(1 < 2)
  {
    yesCounter = 0;
    noCounter = 0;
    for(i = 0; i < 1000; i++)
    {
      x = -1.0f + 2.0f * (float)rand()/((float)RAND_MAX/1);
      y = -1.0f + 2.0f * (float)rand()/((float)RAND_MAX/1);
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

int main()
{
  int yesCounter, noCounter, i;
  struct Main2ThrMain transmData;

  key_t key = ftok("key", 0);
  printf("key = %d\n", key);
  transmData.semId = semget(key, 1, IPC_CREAT | 0666);
  printf("semId = %d\n", transmData.semId);
  transmData.shmId = shmget(key, 2*sizeof(double), IPC_CREAT | 0777);
  printf("shmId = %d\n", transmData.shmId);

  int *data = shmat(transmData.shmId, 0, 0);
  data[0] = 0;
  data[1] = 0;
  printf("1\n");
  printf("data[0]= %d\n", data[0]);
  printf("data[1] = %d\n", data[1]);

  pthread_t threadIndex[threadsCount];
  for(i; i < threadsCount; i++)
  {
    printf("3\n");
    threadIndex[i] = i;
    pthread_create(&(threadIndex[i]), 0, ThreadMain, &transmData);
    printf("4\n");
  }
  for(i = 0; i < threadsCount; i++)
  {
    pthread_join(threadIndex[i], 0);
  }
  yesCounter = data[0];
  noCounter = data[1];
  printf("%d\t%d\n", yesCounter, noCounter);
  double pi = 4 * (float)yesCounter / (float)(yesCounter + noCounter);
  printf("Pi = %f\n", pi);
  return 0;
}
