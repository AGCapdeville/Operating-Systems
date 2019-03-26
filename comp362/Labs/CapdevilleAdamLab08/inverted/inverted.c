/**
 * Name: Adam Capdeville
 * Lab/task: Lab 8
 * Date: 03/25/2019
**/

#include "inverted.h"

// "hidden" symbols (i.e., not included in the .h file)

int tableSize;
int frameSize;

int lookUp(PROC *, int, int);
int findOldest(PROC *table);

/*
 * initializes the table for the given sizes of the memory and frame
 * all entries should be zeroed (e.g., calloc())
 */
void initInverted(PROC **table, int msize, int fsize)
{
    // TODO: implement
    frameSize = fsize;
    
    tableSize = msize / fsize;

    // allocate col
    *table = calloc( tableSize, sizeof(PROC) );
}


/*
 * translate a logical address <pid, page, offset> into a physical address
 * if there is no entry for the pid and the page number in the table, it has to be added
 * if there is no room in the table for the new entry, then the oldest entry has to be removed
 */
long translate(PROC *table, int pid, int page, int offset)
{
    // TODO: implement
    struct timespec t_spec;
    clock_gettime(CLOCK_REALTIME, &t_spec);
    int oldest = findOldest(table);
    int exist = lookUp(table, pid, page);
    long physAddr = 0;

    // Does the pid exist?
    if(exist != -1){
        // Yes
        table[exist].timeStamp = t_spec.tv_nsec;
        return (physAddr = exist * frameSize + offset);            
    }else
    {
        // No
        table[oldest].pid = pid;
        table[oldest].page = page;
        table[oldest].timeStamp = t_spec.tv_nsec;
        return (physAddr = oldest * frameSize + offset);            
    }
}

//
// find the entry for a given pid and page
//
int lookUp(PROC *table, int pid, int page)
{
    // TODO: implement
    for(int i = 0; i < tableSize; i++)
    {
        if( table[i].pid == pid && table[i].page == page){
            return i;
        }
    }
    return -1;
}

//
// find the oldest entry (or not used that has the timestamp == 0)
//
int findOldest(PROC *table)
{
    // TODO: implement
    int oldest = 0;
    for(int i = 0; i < tableSize; i++)
    {
        if ( table[i].timeStamp < table[oldest].timeStamp) {
            oldest = i;   
        }
    }
    return oldest;
}
