#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

#define NUM_OF_WRITERS  3
#define NUM_OF_READERS  5

// allowance limit on counts from one counter
#define COUNT_LIMIT 10

// the target value for counting
#define THRESHOLD 20

#define oops(ermsg) { perror(ermsg); exit(errno); }

// shared resource
int count = 0;

pthread_t *threads;

// read write lock
pthread_rwlock_t lock;

void* writer(void *arg)
{
  long my_limit = (long)arg;

  printf("Writer %ld started with count limit of %ld.\n",
         (long)pthread_self(), my_limit);

  int not_done = 1;
  int i;

  for (i = 0; (i < my_limit) || not_done; i++)
  {
    if (pthread_rwlock_wrlock(&lock) < 0) oops("Read-write lock lock");

    count++;
    not_done = ((count < THRESHOLD) ? 1 : 0);

    printf("Writer %ld: count = %d.\n", (long)pthread_self(), count);

    if (pthread_rwlock_unlock(&lock) < 0) oops("Read-write lock unlock");

    sleep(random() % 5);
  }
  pthread_exit(NULL);
}

void* reader(void *arg)
{
  printf("Reader %ld started.\n", (long)pthread_self());

  int not_done = 1;

  while (not_done)
  {
    if (pthread_rwlock_rdlock(&lock) < 0) oops("Read-write lock lock");

    printf("Reader %ld: count = %d.\n", (long)pthread_self(), count);

    not_done = (count < THRESHOLD ? 1 : 0);

    if (pthread_rwlock_unlock(&lock) < 0) oops("Read-write lock unlock");

    sleep(random() % 5);
  }

  pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_attr_t attr;

  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  if (pthread_rwlock_init(&lock, NULL) < 0) oops("Creating a read-write lock");

  // Create the counting threads and the watcher thread

  threads =
    (pthread_t *)calloc(NUM_OF_WRITERS + NUM_OF_READERS, sizeof(pthread_t));

  int i;

  for (i = 0; i < NUM_OF_WRITERS; i++)
    if (pthread_create(threads + i, &attr, writer,
                       (void *)(random() % COUNT_LIMIT)) < 0) oops(
        "Writer thread creation");

  for (i = 0; i < NUM_OF_READERS; i++)
    if (pthread_create(threads + i, &attr, reader, NULL) < 0) oops(
        "Reader thread creation");

  /* Wait for all threads to complete */
  for (i = 0; i < NUM_OF_WRITERS + NUM_OF_READERS; i++)
    if (pthread_join(threads[i], NULL) < 0) oops("Thread joining");

  printf("Back in main all threads joined.");

  /* Clean up and exit */
  pthread_attr_destroy(&attr);
  pthread_rwlock_destroy(&lock);

  pthread_exit(NULL);
}
