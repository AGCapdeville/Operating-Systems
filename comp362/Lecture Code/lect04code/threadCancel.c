/*
 *  threadCancel.c
 *  lab05lect
 *
 *  Created by AJ Bieszczad on 2/17/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define oops(errmsg, errno) { perror(errmsg); exit(errno); }

void *threadfunc(void *parm);

int main(int argc, char **argv)
{
   pthread_t             thread;
   int                   rc=0;
   
   printf("Entering testcase\n");
   
   /* Create a thread using default attributes */
   printf("Create thread using the NULL attributes\n");
   rc = pthread_create(&thread, NULL, threadfunc, NULL);
   if (rc != 0)
      oops("Cannot create a thread.", rc);
   
   sleep(5);

   printf("Canceling the thread\n");
   rc = pthread_cancel(thread);
   if (rc != 0)
      oops("Cannot cancel a thread.", rc);
   
   pthread_join(thread, NULL);
   printf("Join done.\n");

   printf("Main completed.\n");
   return 0;
}

void *threadfunc(void *parm)
{
   {
      printf("Entered secondary thread.\n");
      while (1) {
         printf("Secondary thread is looping...\n");
         //pthread_testcancel();
         sleep(1);
      }
      return NULL;
   }
}
