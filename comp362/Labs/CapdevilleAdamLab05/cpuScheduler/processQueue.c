/**
 * Name: Adam Capdeville
 * Lab/task: Lab 5
 * Date: 02/25/2019 
**/

#include "processQueue.h"

PROCESS *processTable; // an array of all processes
int processTableSize = 0;

PROCESS **readyQueue; // an array of pointers to the processes in the processTable
int readyQueueSize = 0;

int rQueueCapacity = READY_QUEUE_CAPACITY;
int pTableCapacity = PROCESS_TABLE_CAPACITY;

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
{   // TODO: complete DONE
    processTable[processTableSize] = process;
    processTableSize++;
}

void displayProcessTable()
{    // TODO: complete DONE
    printf("PROCESSES:\n\nName\tEntry\tBurst\n");
    for(int i = 0; i < processTableSize; i++)
    {
        printf("%s\t%d\t%d\n",(&processTable[i])->name,(&processTable[i])->entryTime,(&processTable[i])->burstTime);
    }
    printf("\n");    
}

// finds the shortest job in the ready queue and returns its location in the queue
int findShortestJob()
{    // TODO: complete DONE~
    int index = 0;
    int shortest = -1;

    if(readyQueueSize == 0) {
        return shortest;
    }else
    {
        shortest = 0;
    }

    while(index < readyQueueSize){
        
        if(readyQueueSize == 1){
            shortest = 0;
            index++;
        }else if(readyQueue[shortest]->burstTime > readyQueue[index]->burstTime){
            shortest = index;
        }

        index++;
    }
    return shortest;
}

// adds any processes that arrive at the current time to the readyQueue
void addArrivingProcessToReadyQ(int time)
{
    for (int i = 0; i < processTableSize; i++){
        if (processTable[i].entryTime == time){
            addProcessToReadyQueue(&processTable[i]);
        }
    }
}

// determines if any processes in the process queue have more to execute
bool processesLeftToExecute()
{   // TODO: complete DONE
    for(int index = 0; index < processTableSize; index++)
    {
        if(processTable[index].burstTime != 0)
            return true;
    }
    return false; //return 0 if all processes are complete
}

// adds a pointer and expands the ready queue if necessary
void addProcessToReadyQueue(PROCESS *pointer)
{// TODO: complete DONE
    readyQueue[readyQueueSize++] = pointer;
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
{   // TODO: complete
    PROCESS *removed = NULL;
    removed = readyQueue[index];

    for(int i = index; i < readyQueueSize; i++)
    {
        if(readyQueue[i+1] != NULL) {
            if(i<readyQueueSize)
                readyQueue[i] = readyQueue[i+1];
            else
                readyQueue[i] = NULL;
        }
    }
    readyQueueSize--;
    return removed;
}

// get size of the ready queue
int getReadyQueueSize()
{
    return readyQueueSize;
}

// displays the contents of the ready queue
void displayQueue()
{    // TODO: complete
    printf("QUEUE: ");
    
    if(readyQueueSize == 0)
        printf(" <empty>");

    for(int i = 0; i < readyQueueSize; i++)
    {
        printf("%s(%d) ",(readyQueue[i])->name,(readyQueue[i])->burstTime);
    }
    
}

// calculates the average wait time using information in the proc_queue
// and prints the value.
void printAverageWaitTime()
{   // TODO: complete !!! NOT DONE !!!
    // SUM_OF_AVG_WAIT / NUMBER OF PROCCES
    int avgWait = 0;
    
    for(int i = 0; i < processTableSize; i++)
    {
        printf("Process: %s Wait Time: %0.2f\n", processTable[i].name, (float) processTable[i].waitTime);
        avgWait += processTable[i].waitTime;
    }
    printf("Average Wait Time: %0.2f\n",(float)(avgWait)/(processTableSize));
    
   // processTable
    
}

// clean-up the table and the queue
void cleanUp()
{
    free(processTable);
    free(readyQueue);
}




