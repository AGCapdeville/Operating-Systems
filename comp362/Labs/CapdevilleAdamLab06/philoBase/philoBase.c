/**
 * Name: Adam Capdeville
 * Lab/task: Lab 6
 * Date: 02/28/2019 
**/

#include "philoBase.h"

int main(int argc, char **argv)
{
    if (argc < 3)
    {
        printf("Usage: philosophers <number of seats> <number of turns>");
        return 1;
    }

    numOfSeats = strtod(argv[1], NULL);
    numOfTurns = strtod(argv[2], NULL);
    pthread_mutex_t monitor_mutex = PTHREAD_MUTEX_INITIALIZER;

    initialization_state_and_self();

    // set the see for random number generator
    srand(time(NULL));

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    printf("Start a dinner for %d diners\n", numOfSeats);
    pthread_t * philosopher_tid = calloc(numOfSeats, sizeof(pthread_t));


    long i = 0;
    for ( ; i < numOfSeats; i++)
        pthread_create(&philosopher_tid[i], NULL, philosopher, (void *) i);
    for (i = 0; i < numOfSeats; i++)
        pthread_join(philosopher_tid[i], NULL);


    pthread_mutex_destroy(&monitor_mutex);
    printf("Dinner is no more.\n");
    free(philosopher_tid);
    free(state);
    free(self);
    return 0;
}

void * philosopher(void *num)
{
    int id = (long) num;

    printf("Philosopher no. %d sits at the table.\n", id);

    // philosophers arrive at the table at various times
    usleep(DELAY);

    int i;
    for (i = 0; i < numOfTurns; i++)
    {
        monitor(id,i);
    }

    /*    
        printf("Philsopher no. %d gets hungry for the %d time!\n", id, i + 1); -

        printf("Philsopher no. %d tries to grab chopstick %d\n", id, id); -
        pthread_mutex_lock(&(chopstick[id]));
        printf("Philsopher no. %d has grabbed chopstick %d\n", id, id); -
        
        usleep(DELAY * 1);

        printf("Philsopher no. %d tries to grab chopstic %d\n", id, (id + 1) % numOfSeats); -
        pthread_mutex_lock(&(chopstick[(id + 1) % numOfSeats]));
        printf("Philsopher no. %d grabbed chopstick %d\n", id, (id + 1) % numOfSeats);

        // YEEEAAAAH !!!
        printf("Philsopher no. %d eating\n", id);

        // usleep (DELAY);

        printf("Philsopher no. %d stopped eating\n", id);
        pthread_mutex_unlock(&(chopstick[id]));
        printf("Philsopher no. %d has returned chopstick %d\n", id, id);
        usleep(DELAY * 1);
        pthread_mutex_unlock(&(chopstick[(id + 1) % numOfSeats]));
        printf("Philsopher no. %d has returned chopstick %d\n", id, (id + 1) % numOfSeats);

        printf("Philsopher no. %d finished turn %d\n", id, i + 1);
    }
    */

    printf(">>>>>> Philosopher no. %d finished meal. <<<<<<\n\n", id);
    pthread_exit(NULL);
}

void monitor(int id, int turn)
{
    state[id] = HUNGRY;
    printf("Philosopher no. %d gets hungry for the %d time!\n", id, (turn + 1));
    printf("Philosopher no. %d tries to grab chopsticks\n", id);
    pickup(id);

    // EAT
    usleep(DELAY); 

    putdown(id); 
    printf("Philosopher no. %d finished turn %d\n", id, turn + 1);
}


void pickup (int id)
{ 
    while( state[id] != EATING ){
        lockMutex(id);
        // If you can eat:
        if ( (state[(id+1) % numOfSeats] != EATING) && (state[ (id+(numOfSeats-1)) % numOfSeats] != EATING) ){
            printf("Philosopher no. %d is eating\n", id);
            state[id] = EATING;
        }
        unlockMutex(id);
    }

} 

void putdown (int id)
{
    lockMutex(id);
    state[id] = THINKING;
    printf("Philosopher no. %d has returned their chopsticks\n", id);
    printf("Philosopher no. %d stopped eating\n", id); 
    unlockMutex(id);
}

void lockMutex(int id){
    //if locked
    while(!pthread_mutex_lock(&monitor_mutex)){
        pthread_cond_wait(&self[id], &monitor_mutex);         // wait to eat
    }
}

void unlockMutex(int id){
    pthread_mutex_unlock(&monitor_mutex);
    // Let everyone know they can eat.
    pthread_cond_signal(&self[id]);
}

void initialization_state_and_self()
{ 
    state = malloc( sizeof(int) * numOfSeats);
    self = malloc( sizeof(pthread_cond_t) * numOfSeats);

    for (int i = 0; i < numOfSeats; i++){ 
        state[i] = THINKING;
        pthread_cond_init(&self[i],NULL);   
    }
} 

