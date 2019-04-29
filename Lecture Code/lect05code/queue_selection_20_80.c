#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
   srandom(time(NULL));
   double r = ((double)random())/RAND_MAX;
   printf("r = %lf\n", r);
   if (r < 0.2)
      printf("Select from 20%% queue\n");
   else
      printf("Select from 80%% queue\n");
}
