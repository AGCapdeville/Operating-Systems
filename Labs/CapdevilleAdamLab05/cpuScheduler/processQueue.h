#ifndef _PROCESS_QUEUE_H
#define _PROCESS_QUEUE_H

#define _POSIX_C_SOURCE 200809L // to deal with the crazy "implicit declaration of getline()
// OR #define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PROCESS_TABLE_CAPACITY 64
#define READY_QUEUE_CAPACITY 64

typedef struct proc
{
    char name[8];
    int entryTime; // time of entry to the system 
    int burstTime; // tick to run
    int offTime; // time when cpu lost, ...(the time when the proc leaves the ready Queue)
    int waitTime; // accumulative waiting time, (time waiting in Queue)
} PROCESS;

// process table functions

void createProcessTable(int capacity);

void addArrivingProcessToReadyQ(int time);

void addProcessToTable(PROCESS process);

int findShortestJob();

bool processesLeftToExecute();

void displayProcessTable();

// process ready queue functions

void createReadyQueue(int capacity);

int getReadyQueueSize();

void addProcessToReadyQueue(PROCESS *process);

PROCESS *getProcessFromReadyQueue(int index);

PROCESS *fetchProcessFromReadyQueue(int index);

PROCESS *removeProcessFromReadyQueue(int index);

int findShortestJob();

void displayQueue();

void printAverageWaitTime();

void cleanUp();

#endif
