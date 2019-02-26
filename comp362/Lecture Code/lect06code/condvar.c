#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>

#define oops(ermsg)    { perror(ermsg); exit(errno); }

#define NUM_OF_COUNTERS    10

// allowance limit on counts from one counter
#define COUNT_LIMIT        10

// the target value for counting
#define THRESHOLD          20

// shared resource
int             count = 0;

pthread_t       *threads;

pthread_mutex_t count_mutex;
pthread_cond_t  count_threshold_cv;

void *counter(void *arg)
{
    long myCountLimit = (long) arg;

    printf("Counter %x:  started with count limit of %ld.\n", (unsigned int) pthread_self(), myCountLimit);

    int i;
    for (i = 0; i < myCountLimit; i++)
    {
        if (pthread_mutex_lock(&count_mutex) < 0)
            oops("Mutex lock");

        count++;

        if (count >= THRESHOLD)
        {
            if (pthread_cond_signal(&count_threshold_cv) < 0)
                oops("Conditional variable signal");

            printf("Counter %x, count = %d:  threshold reached.\n", (unsigned int) pthread_self(), count);
        }

        printf("Counter %x, count = %d: unlocking mutex.\n", (unsigned int) pthread_self(), count);

        if (pthread_mutex_unlock(&count_mutex) < 0)
            oops("Mutex unlock");

        sleep(random() % 5);
    }

    pthread_exit(NULL);
}

void *watcher(void *arg)
{
    printf("Wacther %x: started.\n", (unsigned int) pthread_self());

    if (pthread_mutex_lock(&count_mutex) < 0)
        oops("Mutex lock");

    // block here until a signal indicating that the variable has reached
	// the threshold arrives
    printf("Watcher %x: waiting for a signal.\n", (unsigned int) pthread_self());

	// this must be done inside the section protected by the associated mutex
    pthread_cond_wait(&count_threshold_cv, &count_mutex);

    printf("Watcher %x: condition signal received.\n", (unsigned int) pthread_self());

    if (pthread_mutex_unlock(&count_mutex) < 0)
        oops("Mutex unlock");

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
  pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_mutex_init(&count_mutex, NULL);
    pthread_cond_init(&count_threshold_cv, NULL);

    // Create the counting threads and the watcher thread

    threads = (pthread_t *) calloc(NUM_OF_COUNTERS + 1, sizeof(pthread_t));

    int i;
    for (i = 0; i < NUM_OF_COUNTERS; i++)
    {
        if (pthread_create(threads + i, &attr, counter, (void *) (random() % COUNT_LIMIT)) < 0)
            oops("Thread creation");
    }

    pthread_create(threads + i, NULL, watcher, NULL);

    // wait for the watcher
    pthread_join(threads[i], NULL);

    /* Could also wait for all other threads to complete */

    for (i = 0; i < NUM_OF_COUNTERS; i++)
    {
        pthread_join(threads[i], NULL);
    }
    printf ("Main(): Joined on %d  threads. Done.\n", NUM_OF_COUNTERS + 1);

    /* Clean up and exit */
    pthread_attr_destroy(&attr);
    pthread_mutex_destroy(&count_mutex);
    pthread_cond_destroy(&count_threshold_cv);

    exit(EXIT_SUCCESS);
}
