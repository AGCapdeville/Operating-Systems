#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
   srandom(time(NULL));
   double r = ((double)random())/RAND_MAX;
   printf("r = %lf\n", r);
   if (r < 0.1)
      printf("Hit 1st slice\n");
   else if (r < 0.25)
      printf("Hit 2nd slice\n");
   else if (r < 0.5)
      printf("Hit 3rd slice\n");
   else if (r < 0.65)
      printf("Hit 4th slice\n");
   else if (r < 0.85)
      printf("Hit 5th slice\n");
   else
      printf("Hit 6th slice\n");
} 

