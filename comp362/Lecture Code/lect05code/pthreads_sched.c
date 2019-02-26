#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

#define MIN_PRIORITY 1

#define PRIO_GROUP 2

pthread_t hpt[PRIO_GROUP];
pthread_t mpt[PRIO_GROUP];
pthread_t lpt[PRIO_GROUP];

pthread_barrier_t mybarrier;

void print_scheduling_info(pthread_t thread_id)
{
   int policy;
   char*policyStr;
   struct sched_param param;

   pthread_getschedparam(thread_id, &policy, &param);

   if (policy == SCHED_RR)
      policyStr = "SCHED_RR";
   else if (policy == SCHED_FIFO)
      policyStr = "SCHED_FIFO";
   else if (policy == SCHED_OTHER)
      policyStr = "SCHED_OTHER";

   printf("Thread ID: %d uses %s policy with priority %d\n", (int) thread_id, policyStr, param.sched_priority);
}

void *highprior_thread(void *arg){
pthread_t thread_id = pthread_self();

while(1){
pthread_barrier_wait(&mybarrier);
print_scheduling_info(thread_id);
}

return NULL;
}

void *middleprior_thread(void *arg){
pthread_t thread_id = pthread_self();

while(1){
pthread_barrier_wait(&mybarrier);
print_scheduling_info(thread_id);
}

return NULL;
}

void *lowprior_thread(void *arg){
pthread_t thread_id = pthread_self();
int count = 0;

while(1){
pthread_barrier_wait(&mybarrier);
print_scheduling_info(thread_id);
}

return NULL;
}

int main(int argc, char *argv[]){
struct sched_param my_param;
pthread_attr_t hp_attr;
pthread_attr_t mp_attr;
pthread_attr_t lp_attr;
int i;

/* MAIN-THREAD WITH LOW PRIORITY */
my_param.sched_priority = sched_get_priority_min(SCHED_FIFO);
pthread_setschedparam(pthread_self(), SCHED_RR, &my_param);
print_scheduling_info(pthread_self());


/* SCHEDULING POLICY AND PRIORITY FOR OTHER THREADS */
pthread_attr_init(&lp_attr);
pthread_attr_init(&mp_attr);
pthread_attr_init(&hp_attr);

pthread_attr_setinheritsched(&lp_attr, PTHREAD_EXPLICIT_SCHED);
pthread_attr_setinheritsched(&mp_attr, PTHREAD_EXPLICIT_SCHED);
pthread_attr_setinheritsched(&hp_attr, PTHREAD_EXPLICIT_SCHED);

pthread_attr_setschedpolicy(&lp_attr, SCHED_FIFO);
pthread_attr_setschedpolicy(&mp_attr, SCHED_FIFO);
pthread_attr_setschedpolicy(&hp_attr, SCHED_FIFO);

my_param.sched_priority = MIN_PRIORITY + 1;
pthread_attr_setschedparam(&lp_attr, &my_param);
my_param.sched_priority = MIN_PRIORITY + 2;
pthread_attr_setschedparam(&mp_attr, &my_param);
my_param.sched_priority = MIN_PRIORITY + 3;
pthread_attr_setschedparam(&hp_attr, &my_param);

pthread_barrier_init(&mybarrier, NULL, PRIO_GROUP*3);

for(i=0; i<PRIO_GROUP; i++){
pthread_create(&lpt[i], &lp_attr, lowprior_thread, NULL);
pthread_create(&mpt[i], &mp_attr, middleprior_thread, NULL);
pthread_create(&hpt[i], &hp_attr, highprior_thread, NULL);
}

for(i=0; i<PRIO_GROUP; i++){
pthread_join(hpt[i], NULL);
pthread_join(mpt[i], NULL);
pthread_join(lpt[i], NULL);
}

printf("main exiting\n");

return 0;
}
