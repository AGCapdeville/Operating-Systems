#ifndef _CPU_SCHEDULER_H
#define _CPU_SCHEDULER_H

#define _POSIX_C_SOURCE 200809L // to deal with the crazy "implicit declaration of getline()
// OR #define _GNU_SOURCE

#include <sys/types.h>

#include "processQueue.h"

// contains parameters for functions implementing scheduling algorithms
typedef struct algorithmParams
{
    PROCESS *cpu; // reference to the currently executing process
    char algorithm[8]; // FCFS, SJF, SRTF, RR
	void (*step)(void *); // pointer to the step function we will call
    int quantum; // for RR
    int time; // current time tick
    PROCESS *newProcess; // NULL if no new process at the current time tick
} ALGORITHM_PARAMS;

int readProcessTable();

void doStep(void (*func)(void *), void *);

void fcfsStep(void *param);

void sjfStep(void *param);

void srtfStep(void *param);

void rrStep(void *param);

void displayTimeTick(int, PROCESS*);

#endif
