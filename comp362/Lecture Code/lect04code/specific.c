/*
 *  specific.c
 *  pthread_sync
 *
 *  Created by AJ Bieszczad on 2/17/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define oops(errmsg, errno) { perror(errmsg); exit(errno); }

pthread_t tid; /* the thread identifier */
pthread_attr_t attr; /* set of attributes for the thread */

pthread_key_t key; // key for thread specific data
// it's common to all threads, but the data that is attached to the key
// is different for each thread (using pthread_setspecific())

pthread_once_t init_done = PTHREAD_ONCE_INIT;

void cleaner(void *);
void *runner(void *);

int main(void)
{
   int ret;
   
	/* get the default attributes */
	pthread_attr_init(&attr);
	
   /* create the thread */
   pthread_create(&tid, &attr, runner, NULL);
   pthread_create(&tid, &attr, runner, NULL);
   
   // we need to stop before pthread_key_delete(), since that would exit the
   // program withou givin the thread a chance to call the cleaner
   printf("MAIN: Enter a key to continue.\n");
   getchar();      
   
   if ((ret = pthread_key_delete(key)) != 0)
      oops("Cannot delete thread specific data.\n", ret);
}

void key_init()
{
   int ret;
   
   if ((ret = pthread_key_create(&key, cleaner)) != 0)
      oops("Cannot create thread specific data.\n", ret);
}

void *runner(void *arg)
{
   int ret;
   
   // to avoid so-called race conditions that we will be study later
   pthread_once(&init_done, key_init);
   
   // allocate some space for the thread-specific data
   void *value = (void *) malloc(sizeof(int));
   // set the data to something; here: to threads id (in HEX)
   sprintf(value, "%X", (int) pthread_self());
   
   // this is were OS creates a thread specific data
   if ((ret = pthread_setspecific(key, value)) != 0)
      oops("Cannot set thread specific data.\n", ret);
   
   printf("THREAD %s: Set thread specific data.\n", (char *) value);
   
   // here is how to get the data
   if ((value = pthread_getspecific((pthread_key_t) key)) == NULL)
      oops("Cannot get thread specific data.\n", ret);
   
   printf("THREAD %s: Get thread specific data.\n", (char *) value);

   // not necessary, but might be useful in other cases
   pthread_exit((void *)pthread_self()); 

   return NULL;
}

/*
 a cleaning facility; in this case free() could have been used directly
 in the call, but in general this might be useful for other things
 including cleaning up after some specialization of threads
 */
void cleaner(void *value)
{
   printf("Cleaning up thread specific data: %s\n", (char*)value);
   free(value);
}
