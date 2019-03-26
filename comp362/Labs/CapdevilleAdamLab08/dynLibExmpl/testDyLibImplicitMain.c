#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int giveMeNum();

int main(int argc, char **argv)
{
   int n = giveMeNum();
   printf ("You gave me : %d\n", n);
   return 0;
}
