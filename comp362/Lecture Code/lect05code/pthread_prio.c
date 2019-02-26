#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define PRIORITY 20

void*runner(void*param)
{
   int my_policy;
   struct sched_param my_param;
   int status;

   status = pthread_getschedparam (pthread_self (), &my_policy, &my_param);
   printf ("# :thread_routine running at %s/%d\n",
           ( my_policy == SCHED_FIFO ? "FIFO"
            : ( my_policy == SCHED_RR ? "RR"
               : (my_policy == SCHED_OTHER ? "OTHER"
                  : "unknown") ) ),
           my_param.sched_priority);

   printf( "Hello world from: %d\n", getpid() );
   fflush(stdout);
   return NULL;
}

int main(int argc, char*argv[])
{
   pthread_t tid;
   pthread_attr_t attr;

   // get the default attributes
   pthread_attr_init(&attr);

   // specialize attributes
   struct sched_param schedparam;
   schedparam.sched_priority = PRIORITY;

   pthread_attr_setscope(&attr, PTHREAD_SCOPE_PROCESS);
   pthread_attr_setinheritsched(&attr, PTHREAD_EXPLICIT_SCHED);
   pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
   pthread_attr_setschedparam(&attr, &schedparam);
   pthread_create(&tid, &attr, &runner, &argv);
   pthread_join(tid, NULL);
   pthread_attr_destroy(&attr);
}
