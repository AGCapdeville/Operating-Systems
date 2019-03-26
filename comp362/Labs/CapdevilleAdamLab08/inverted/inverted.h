#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct proc
{
    int pid; // process id
    int page; // page number
    time_t timeStamp; // last reference
} PROC;

void initInverted(PROC **, int memSize, int frameSize);
long translate(PROC *, int, int, int);
