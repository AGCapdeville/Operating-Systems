#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_OF_BEES 5

#define oops(ermsg) { perror(ermsg); exit(errno); }

pthread_mutex_t mutex;
pthread_t *threads;

// shared resource
int r;

void *bee(void *param)
{
	while(true)
	{
      // try to enter the crituca section
      if (pthread_mutex_lock(&mutex) < 0)
         oops("Mutex lock");

      // in critical section
		r = (r + random() % 5) % 5;
		printf("This %ld bee is bzziing for %d seconds :-)\n", (long) pthread_self(), r);
		fflush(stdout);

      sleep(r);

      // exit the critical section
      if (pthread_mutex_unlock(&mutex) < 0)
         oops("Mutex unlock");

      // out of critical section
	}
}

int main(int argc, char *argv[])
{
	int i;

  pthread_mutexattr_t mutex_attr;
#ifdef USE_ADAPTIVE
  pthread_mutexattr_init (&mutex_attr);
  pthread_mutexattr_settype (&mutex_attr, PTHREAD_MUTEX_ADAPTIVE_NP);
#endif

	// initialize the semaphore
	if (pthread_mutex_init(&mutex, &mutex_attr) < 0)
      oops("Mutex initialization");

   // Create a bunch of joinable bees
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
   threads = (pthread_t *) calloc(NUM_OF_BEES, sizeof(pthread_t));
   for(i = 0; i < NUM_OF_BEES; i++)
	{
		if (pthread_create(threads + i, &attr, bee, NULL) < 0)
			oops("Thread creation");
		printf("Bee %ld created\n", (long)(threads + i));
	}

   // wait for the bees
	for(i = 0; i < NUM_OF_BEES; i++)
	{
      if (pthread_join(threads[i], NULL) < 0)
         oops("Thread join");
   }

	pthread_mutex_destroy(&mutex);
   pthread_attr_destroy(&attr);

	return EXIT_SUCCESS;
}


