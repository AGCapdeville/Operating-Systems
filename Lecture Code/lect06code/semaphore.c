#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_OF_BEES 5
#define TRUE 1

#define oops(ermsg) { perror(ermsg); exit(errno); }

sem_t sem;
pthread_t *threads;

// shared resource
int r;

void* bee(void *param)
{
  int delay;

  while (TRUE)
  {
    // wait
    sem_wait(&sem);

    // in critical section
    r = (r + random() % 5) % 5;
    printf("This %ld bee is bzziing for %d seconds :-)\n", (long)pthread_self(),
           r);
    fflush(stdout);

    delay = r;

    // signal
    sem_post(&sem);

    // out of critical section
    sleep(r);
  }
}

int main(int argc, char *argv[])
{
  int i;

  // initialize the semaphore
  if (sem_init(&sem, 0, 0) < 0) oops("Semaphore initialization");

  pthread_attr_t attr;
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  // Create a bunch of bees
  threads = (pthread_t *)calloc(NUM_OF_BEES, sizeof(pthread_t));

  for (i = 0; i < NUM_OF_BEES; i++)
  {
    if (pthread_create(threads + i, &attr, bee, NULL) < 0) oops(
        "Semaphore initialization");
    printf("Bee %ld created\n", (long)threads + i);
  }

  // signal
  sem_post(&sem);

  // wait for the bees
  for (i = 0; i < NUM_OF_BEES; i++)
  {
    if (pthread_join(threads[i], NULL) < 0) oops("Semaphore initialization");
  }
  sem_destroy(&sem);
  pthread_attr_destroy(&attr);
  return 0;
}
