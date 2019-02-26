#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <stdbool.h>

#define NUM_OF_BEES 5

//#define USE_SPINLOCK
//#define USE_ADAPTIVE

#ifdef USE_SPINLOCK
pthread_spinlock_t spinlock;
#else
pthread_mutex_t mutex;
#endif

pthread_t *threads;

// shared resource
int r;

void *bee(void *param)
{
    while (true)
    {
        // try to enter the critical section
#ifdef USE_SPINLOCK
        pthread_spin_lock(&spinlock);
#else
        pthread_mutex_lock(&mutex);
#endif
        // in critical section
        r = (r + random() % 5) % 5;
        printf("This %ld bee is bzziing for %d seconds :-)\n", (long) pthread_self(), r);
        fflush(stdout);

        sleep(r);

        // exit the critical section
#ifdef USE_SPINLOCK
        pthread_spin_unlock(&spinlock);
#else
        pthread_mutex_unlock(&mutex);
#endif

        // out of critical section
    }
}

int main(int argc, char *argv[])
{
    // initialize the semaphore
#ifdef USE_SPINLOCK
    printf("Using spinlocks...\n");
 pthread_spin_init(&spinlock, 0);
#else
    pthread_mutexattr_t mutex_attr;
#ifdef USE_ADAPTIVE
    printf("Using adaptive...\n");
  pthread_mutexattr_init (&mutex_attr);
  pthread_mutexattr_settype (&mutex_attr, PTHREAD_MUTEX_ADAPTIVE_NP);
#endif
    printf("mutex locks...\n");
    pthread_mutex_init(&mutex, &mutex_attr);
#endif

    int i;

    pthread_attr_t attr;
    pthread_attr_init(&attr);

    // Create a bunch of bees
    threads = (pthread_t *) calloc(NUM_OF_BEES, sizeof(pthread_t));
    for (i = 0; i < NUM_OF_BEES; i++)
    {
        pthread_create(threads + i, &attr, bee, NULL);
        printf("Bee %ld created\n", (long) threads[i]);
    }

    // wait for the bees
    for (i = 0; i < NUM_OF_BEES; i++)
        pthread_join(threads[i], NULL);

#ifdef USE_SPINLOCK
    pthread_spin_destroy(&spinlock);
#else
    pthread_mutex_destroy(&mutex);
#endif
    pthread_attr_destroy(&attr);

    return 0;
}


