/**
 * Name: Adam Capdeville
 * Lab/task: Lab 5
 * Date: 02/25/2019 
**/

#include "cpuScheduler.h"

int main()
{
    // send text file to stdin
    freopen("../../in.txt", "r", stdin);

    int time = 0; // simulated time

    ALGORITHM_PARAMS parameters = {NULL, "", NULL, 0, 0, NULL}; // simulation parameters

    // read the algorithm type and time quantum if necessary
    scanf("%s", parameters.algorithm);

    //check which algorithm was passed, set values accordingly
    if (strcmp(parameters.algorithm, "RR") == 0)
    {
        scanf("%d", &parameters.quantum);
        parameters.step = &rrStep;
    }
    else if (strcmp(parameters.algorithm, "FCFS") == 0)
        parameters.step = &fcfsStep;
    else if (strcmp(parameters.algorithm, "SJF") == 0)
        parameters.step = &sjfStep;
    else if (strcmp(parameters.algorithm, "SRTF") == 0)
        parameters.step = &srtfStep;
    else
    {
        printf("The job type input is not a valid input!");
        exit(EXIT_FAILURE);
    }

    // skip over the enf of line marker
    scanf("\n");

    printf("\nALGORITHM: %s", parameters.algorithm);
    if (strcmp(parameters.algorithm, "RR") == 0)
        printf("%3d", parameters.quantum);
    printf("\n\n");

    createProcessTable(PROCESS_TABLE_CAPACITY); //create process table
    createReadyQueue(READY_QUEUE_CAPACITY);//create queue with size == number of processes

    readProcessTable(); //populate process table

    displayProcessTable();

    printf("SIMULATION:\n\n");

    while (processesLeftToExecute())
    {
        addArrivingProcessToReadyQ(time);
        
        parameters.time = time;

        doStep(parameters.step, &parameters);

        displayTimeTick(time, parameters.cpu);

        if (parameters.cpu != NULL)
            parameters.cpu->burstTime--;

        time++;        
       // while(time == 20);        
    }

    printAverageWaitTime();

    cleanUp();

    return EXIT_SUCCESS;
}

// step executor
void doStep(void (*func)(void *), void *param)
{
    func(param);
}

// function implementing a step of FCFS
void fcfsStep(void *param)
{
    ALGORITHM_PARAMS *p = (ALGORITHM_PARAMS *) param;

    //if the cpu has nothing currently executing
    if (p->cpu == NULL || p->cpu->burstTime == 0) {
        p->cpu = fetchProcessFromReadyQueue(0); //start executing the first process in the ready queue
        if (p->cpu != NULL)
            p->cpu->waitTime = p->time - p->cpu->entryTime; // update the wait time
    }
}

// function implementing a step of SJF
void sjfStep(void *param)
{    // TODO: implement
    ALGORITHM_PARAMS *p = (ALGORITHM_PARAMS *) param;    
    int location = 0;
    
    //if the cpu has nothing currently executing
    if (p->cpu == NULL || p->cpu->burstTime == 0) {
        // Find next shortest job:
        location = findShortestJob();
        if(location == -1) // stay the course
            location = 0;

        p->cpu = fetchProcessFromReadyQueue(location); // work on proc
        if (p->cpu != NULL)
            p->cpu->waitTime = p->time - p->cpu->entryTime; // update the wait time
    }
}

// function implementing a step of SRTF
void srtfStep(void *param)
{    // TODO: implement - - Shortest Remaining Time First
    ALGORITHM_PARAMS *p = (ALGORITHM_PARAMS *) param;

    /*algo* 
        if (p.cpu == NULL || p.cpu.burstTime == 0|| getProcessFromReadyQueue(findShortestJob()).burstTime < p.cpu.burstTime)
        we're gonna check the p.cpu burst time to see if it's greater than zero
        if it's > 0, 
            add back the current process to the ready queue
            set the processes.offtime = p.time
        get new cpu by fetching
        if (the process's offtime == 0)
            waitTime = time - entryTime
        else
            waitTime += time - offtime
    **/        
    if(p->cpu == NULL)
        p->cpu = fetchProcessFromReadyQueue(0);

    
    //printf("readyQueue size: %d \t shortest: %d\n", getReadyQueueSize(), findShortestJob());

    if(findShortestJob() >= 0){
        if( getProcessFromReadyQueue(findShortestJob())->burstTime < p->cpu->burstTime ){
            
            if(p->cpu->burstTime > 0){
                p->cpu->offTime = p->time;
                addProcessToReadyQueue(p->cpu);
            }

            printf("\n");
            displayQueue();
            printf("\n");

            printf("shortest job: %d\n", findShortestJob());

            p->cpu = fetchProcessFromReadyQueue(findShortestJob());

        }
    }

    if (p->cpu->burstTime == 0){
        p->cpu = fetchProcessFromReadyQueue(findShortestJob());
        if(p->cpu->offTime == 0){
            p->cpu->waitTime = p->time - p->cpu->entryTime;
        }else{
            p->cpu->waitTime += p->time - p->cpu->offTime;    
        }
    }
}
// function implementing a step of RR
void rrStep(void *param)
{    // TODO: implement - Not working...
    ALGORITHM_PARAMS *p = (ALGORITHM_PARAMS *) param;
    static int rrCounter; // counter to keep track of how many more ticks the process in cpu has left
    
    if (p->cpu == NULL){ // Initial setup:
        p->cpu = fetchProcessFromReadyQueue(0);
        rrCounter = p->quantum;
    }else if (p->cpu->burstTime == 0){   // If current proc is done before the timer runs out:
        if(p->cpu->offTime == 0){
            p->cpu->waitTime = p->time - p->cpu->entryTime;
        }else{
            p->cpu->waitTime += p->time - p->cpu->offTime;    
        }
        p->cpu = fetchProcessFromReadyQueue(0); // Remove and Fetch
        rrCounter = p->quantum; // restart the timer
    }else if(rrCounter == 0){
        p->cpu->offTime = p->time;
        addProcessToReadyQueue(p->cpu);         // push proc back onto ready Queue
        p->cpu = fetchProcessFromReadyQueue(0);
        rrCounter = p->quantum;
    }else{
    p->cpu = fetchProcessFromReadyQueue(0); // Remove and Fetch
    }
    
    rrCounter--;
    // make sure to remove p-cpu properly , specificly the second one.
}

//fills the processTable with processes from input
int readProcessTable()
{
    PROCESS tempProcess = {
        .name = "", 
        .entryTime = 0, 
        .burstTime = 0, 
        .offTime = 0, 
        .waitTime = 0
    };

    char *line = NULL;
    char *currPos;
    size_t len = 0;

    int counter = 0;
    int offset = 0;

    while (getline(&line, &len, stdin) != -1)
    {
        currPos = line;
        sscanf(currPos, "%s%n", tempProcess.name, &offset);
        currPos += offset;
        sscanf(currPos, "%d%n", &tempProcess.entryTime, &offset);
        currPos += offset;
        sscanf(currPos, "%d", &tempProcess.burstTime);

        addProcessToTable(tempProcess);

        free(line);
        line = NULL;

        counter++;
    }

    free(line);

    return counter;
}

void displayTimeTick(int time, PROCESS *cpu)
{
    printf("T%d:\nCPU: ", time);
    if (cpu == NULL)
        printf("<idle>\n");
    else
        printf("%s(%d)\n", cpu->name, cpu->burstTime);

    displayQueue();
    printf("\n\n");
}






