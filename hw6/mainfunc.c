#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  double x, y;
  int yesCounter = 0, noCounter = 0;
  int exTime = 10;
  clock_t start;
  start = clock() / CLOCKS_PER_SEC;
  
  while((clock() / CLOCKS_PER_SEC) - start < exTime)
  {
    x = -1.0f + 2.0f * (float)rand()/((float)RAND_MAX/1);
    y = -1.0f + 2.0f * (float)rand()/((float)RAND_MAX/1);
    if (x*x + y*y <= 1)
      yesCounter++;
    else
      noCounter++;
  }
  printf("%d\t%d\n", yesCounter, noCounter);
  double pi = 4 * (float)yesCounter / (float)(yesCounter + noCounter);
  printf("Pi = %f\n", pi);
  return 0;
}
