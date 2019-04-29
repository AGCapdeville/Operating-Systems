/**
 * Name: Adam Capdeville
 * Lab/task: Lab 6
 * Date: 02/28/2019 
**/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

#define DELAY ( (rand() % 5 + 1) * 1000)

// FUNCTIONS:
void *philosopher(void *id);

void initialization_state_and_self();
void monitor(int id, int turn);
void pickup (int id);
void putdown (int id);
void test (int id);

void unlockMutex(int id);
void lockMutex(int id);

// GLOBALS :
int numOfSeats, numOfTurns;
enum { THINKING, HUNGRY, EATING}; 
int* state;

pthread_mutex_t monitor_mutex;
pthread_cond_t* self;




