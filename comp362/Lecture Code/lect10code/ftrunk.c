#include <stdio.h>  //for fopen, perror
#include <unistd.h> //for ftruncate
#include <stdlib.h> // for exit

#define oops(msg, errn) { perror(msg); exit(errn); }

int main()
{
   // without opening
   if (truncate("test.txt", 100000) == -1)
   {
      oops("Could not truncate", 1);
   }
   
   // when file is already opened
   FILE *file = fopen("test.txt", "r+");
   if (file == NULL)
   {
      oops("Could not open file", 1);
   }
   
   //do something with the contents of file
   if (ftruncate(fileno(file), 100000) == -1)
   {
      oops("Could not truncate", 2);
   }
   
   fclose(file);
   return 0;
}
