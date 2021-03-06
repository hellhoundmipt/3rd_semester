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
  int exTime = 20;
  clock_t start;
  start = clock() / CLOCKS_PER_SEC;

  while((clock() / CLOCKS_PER_SEC) - start < exTime)
  {
    //x = -1.0f + 2.0f * (float)rand()/((float)RAND_MAX/1);
    //y = -1.0f + 2.0f * (float)rand()/((float)RAND_MAX/1);
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
  fprintf(resfile, "1 thread pi = %f\tyesCounter = %d\tnoCounter = %d\n\n", pi, yesCounter, noCounter);
  fclose(resfile);
  return 0;
}
