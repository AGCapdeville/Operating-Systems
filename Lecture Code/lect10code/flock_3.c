#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>

#define oops(msg, errn)    { perror(msg); exit(errn); }

char line[256];
FILE* fh;

void *runner(void *param); // the thread

int main(int argc, char *argv[])
{
   if ((fh = fopen("test.txt", "r")) == NULL)
      oops("Failed to open file!", 1);
   
   pthread_t tid; // the thread identifier
   
   // create the threads
   pthread_create(&tid, NULL, runner, 1);
   pthread_create(&tid, NULL, runner, 2);
   pthread_create(&tid, NULL, runner, 3);
   
   printf("Press <RETURN> to terminate\n");
   getchar();
   printf("<RETURN> pressed by the user. Process is terminating.\n");
   
   fclose(fh);
}

void *runner(void *param)
{
   while(1)
   {
      //    flockfile(fh); // blocking version
      
      while (ftrylockfile(fh) != 0) // non-blocking version
      {
//         printf("Thread %d failed to lock a file...\n", (int)param);
         sleep(rand()%2);
      }
      
      printf("Thread %d locked the file...\n", (int)param);
      
      sleep(rand()%3);
      
      funlockfile(fh);
      
      printf("Thread %d unlocked the file...\n", (int)param);
   }
}