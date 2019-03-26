#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

int main(int argc, char **argv)
{
   void *dylibHandle;
   char *error;
   
   dylibHandle = dlopen ("./libgiveMeNum.so", RTLD_LAZY);
   if (!dylibHandle)
   {
      fprintf (stderr, "ERR: %s\n", dlerror());
      exit(1);
   }
   // clear any existing errors
   dlerror();
   
   int (*giveMeNum)() = dlsym(dylibHandle, "giveMeNum");
   int n = (*giveMeNum)();
   if ((error = dlerror()) != NULL)
   {
      fprintf (stderr, "ERR: %s\n", error);
      exit(1);
   }
   printf ("You gave me : %d\n", n);
   dlclose(dylibHandle);
   return 0;
}
