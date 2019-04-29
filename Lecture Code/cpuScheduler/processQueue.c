#include "processQueue.h"

PROCESS *processTable; // an array of all processes
int processTableSize = 0;

PROCESS **readyQueue; // an array of pointers to the processes in the processTable
int readyQueueSize = 0;

// constructor of the process table
void createProcessTable(int capacity)
{
    processTable = (PROCESS *) malloc(capacity * sizeof(PROCESS));
}

// constructor of the ready queue
void createReadyQueue(int capacity)
{
    readyQueue = (PROCESS **) malloc(capacity * sizeof(PROCESS *));
}

// adds a process to the table
void addProcessToTable(PROCESS process)
{
    // TODO: complete
}

void displayProcessTable()
{
    printf("PROCESSES:\nName    \tEntry\tBurst\n");

    // TODO: complete

    printf("\n");
}

// finds the shortest job in the ready queue and returns its location in the queue
int findShortestJob()
{
    int shortest = -1;

    // TODO: complete

    return shortest;
}

// adds any processes that arrive at the current time to the readyQueue
PROCESS * arrivingProcess(int time)
{
    // TODO: complete

    return NULL;
}

// determines if any processes in the process queue have more to execute
bool processesLeftToExecute()
{
    // TODO: complete

    return false; //return 0 if all processes are complete
}

// adds a pointer and expands the ready queue if necessary
void addProcessToReadyQueue(PROCESS *pointer)
{
    // TODO: complete
}

// exposes a specific process in the ready queue (it stays in the queue)
PROCESS *getProcessFromReadyQueue(int index)
{
    return readyQueue[index];
}

// gets a specific process from the ready queue (it gets removed from the queue)
PROCESS *fetchProcessFromReadyQueue(int index)
{
    PROCESS *proc = readyQueue[index];

    removeProcessFromReadyQueue(index);

    return proc;
}

// removes the process at index from the ready queue and returns a pointer to it
PROCESS *removeProcessFromReadyQueue(int index)
{
    PROCESS *removed = NULL;

    // TODO: complete

    return removed;
}

// get size of the ready queue
int getReadyQueueSize()
{
    return readyQueueSize;
}

// displays the contents of the ready queue
void displayQueue()
{
    // TODO: complete
}

// calculates the average wait time using information in the proc_queue
// and prints the value.
void printAverageWaitTime()
{
    // TODO: complete
}

// clean-up the table and the queue
void cleanUp()
{
    free(processTable);
    free(readyQueue);
}




