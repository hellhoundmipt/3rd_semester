#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
  double x;
  struct drand48_data *buffer;
  long int seedval;
  int size = sizeof(struct drand48_data);
  srand48_r(seedval, buffer);
  int i = 0;
  for(i; i < 100; i++)
  {
    drand48_r(buffer, &x);
    x = -1.0f + 2.0f * x;
    printf("X = %f\n", x);
  }
  printf("Size = %d\n", size);
  return 0;
}
