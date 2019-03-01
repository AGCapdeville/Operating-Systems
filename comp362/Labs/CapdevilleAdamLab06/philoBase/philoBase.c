/**
 * Name: Adam Capdeville
 * Lab/task: Lab 6
 * Date: 02/28/2019 
**/

#include "philoBase.h"

pthread_mutex_t monitor_mutex;

int numOfSeats, numOfTurns;
enum { THINKING, HUNGRY, EATING}; 
int* state;

pthread_cond_t* self;

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

    pthread_t philosopher_tid[numOfSeats];


    long i;

    for (i = 0; i < numOfSeats; i++)
        pthread_create(&philosopher_tid[i], NULL, philosopher, (void *) i);

    for (i = 0; i < numOfSeats; i++)
        pthread_join(philosopher_tid[i], NULL);

    pthread_mutex_destroy(&monitor_mutex);

    printf("Dinner is no more.\n");

    return 0;
}

void *philosopher(void *num)
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

    //for (i = 0; i < numOfSeats; i++)
    //    pthread_mutex_destroy(i);

    printf(">>>>>> Philosopher no. %d finished meal. <<<<<<\n\n", id);

    pthread_exit(NULL);
}

void monitor(int id, int turn)
{
    pthread_cond_wait( &self[id] , &monitor_mutex);
    printf("Philosopher no. %d gets hungry for the %d time!\n", id, (turn + 1));

    pickup(id);

    // EAT
    usleep(DELAY); 

    putdown(id); 
    
        // we signal in putdown:
    //signal(monitor_mutex);
    //pthread_cond_signal( (&self)[id] );

    printf("Philosopher no. %d finished turn %d\n", id, turn + 1);
}


void pickup (int i)
{ 

    state[i] = HUNGRY; 

    printf("Philosopher no. %d tries to grab chopsticks\n", i);
    test(i);
     
    if (state[i] != EATING){ // If not eating wait:
        printf("Philosopher no. %d is waiting\n", i);
        pthread_cond_wait( &self[i] , &monitor_mutex); // waiting for signal
        //pickup(i);  // lets try picking up again.
        
        pthread_mutex_lock( &monitor_mutex );
        state[i] = EATING; // Now start eating

    }else
    {   // if eating:
        pthread_mutex_lock( &monitor_mutex );
        printf("Philosopher no. %d is eating\n", i);
    }
    
} 

void putdown (int i)
{ 
    pthread_mutex_unlock(&monitor_mutex);
    state[i] = THINKING;
    printf("Philosopher no. %d has returned their chopsticks\n", i);
    printf("Philosopher no. %d stopped eating\n", i);
    // test left and right neighbors
    test((i + 1) % numOfSeats);
    test((i - 1) % numOfSeats);
} 

void test (int i)
{ 
    if ( (state[(i+1) % numOfSeats] != EATING) 
        && (state[i] == HUNGRY) 
        && (state[(i-1) % numOfSeats] != EATING) )
    { 
        state[i] = EATING;
        printf("Philosopher no. %d is eating\n",i);
        pthread_cond_signal(&self[i]);
    } 
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

