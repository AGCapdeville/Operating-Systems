/**
 * Name: Adam Capdeville
 * Lab/task: Lab 9
 * Date: 04/01/2019
**/
/**
 * This implements the LRU page-replacement algorithm.
 */

#include "replace.h"

FRAME *pageTableTop;
int pageTableSize = 0;
FRAME *leastRecentlyUsed;


int numOfFrames = 0;

// statistics
int numOfFaults = 0;

int hitIndex;

/*
 * insert pages from a reference string into a page table and measure
 * the page fault rate
 */
int testLRU(int numOfFrames, int *refString, int refStrLen)
{
    // TODO: implement
    pageTableTop = NULL;

    numOfFrames = numOfFrames;

    for(int i = 0; i < numOfFrames; i++)
    {
        // pageTableTop = initTable(pageTableTop);  
        FRAME* newFrame = malloc(sizeof(FRAME));

        if(pageTableTop == NULL){
            newFrame->over = NULL;
            newFrame->pageNumber = FREE_SLOT;
            newFrame->under = NULL;
        }else
        {
            pageTableTop->under = newFrame;
            newFrame->over = pageTableTop;
            newFrame->pageNumber = FREE_SLOT;
            newFrame->under = NULL;
        }

        pageTableTop = newFrame;
        printf("count: i \n");


    }
    while(pageTableTop->over != NULL){
        pageTableTop = pageTableTop->over;
    }
    leastRecentlyUsed = pageTableTop;

    for(int i = 0; i < refStrLen ; i++)
    {
        printf("%d ->\t",refString[i]);
        insertLRU(refString[i]);
    }

    //return the page fault rate: 
    printf("Number of page faults using LRU: %d",numOfFaults);

    return 0;
}



/*
 *	try to insert a page into the page table
 */
void insertLRU(int pageNumber)
{
    // TODO: implement
    hitIndex = -2;

    FRAME* foundPage;
    foundPage = pageTableTop;

    if (pageTableSize == 0) {
        pageTableTop->pageNumber = pageNumber; //
        leastRecentlyUsed = pageTableTop;
        pageTableSize++;
    }else
    {
        foundPage = searchLRU(pageNumber);

        if ( foundPage == NULL )
        {   //not found
            //insert at top
            
            // increase size:
        pageTableSize++;
        if(pageTableSize > numOfFrames){
            
            //need to delete the tail..
            leastRecentlyUsed = leastRecentlyUsed->over
            
        }else
        {
            foundPage = pageTableTop;
            int holdPrevPage = pageNumber;
            int holdCurrPage = foundPage->pageNumber;
            
            foundPage->pageNumber = pageNumber;  // set top page number = the inserting page number

            for(int i = 0; i < pageTableSize; i++)
            {
                foundPage->pageNumber = holdPrevPage;
                foundPage = foundPage->under;
                holdPrevPage = holdCurrPage;
                holdCurrPage = foundPage->pageNumber;
            }
        }

        }else
        {   //found
            //move currentFrame (aka found frame) to Top
            if(hitIndex == 0){ //currently at top
                //do nothing, already at top
            }else if(hitIndex == pageTableSize){ //currently at bot
                foundPage->over->under = foundPage->under;
                leastRecentlyUsed = foundPage->over;
                foundPage->over = NULL;
                foundPage->under = pageTableTop;
                pageTableTop->over = foundPage;
                pageTableTop = foundPage;

            }else{ //in middle somwhere
            foundPage->over->under = foundPage->under;
            foundPage->under->over = foundPage->over;
            pageTableTop->over = foundPage;
            foundPage->under = foundPage;
            foundPage->over = NULL;
            pageTableTop = foundPage;
            }
            
        }
        
    }
    displayLRU();  
}


/**
 * Searches for page pageNumber in the page frame list
 * returns NULL if a frame with pageNumber was not found
 * otherwise, returns a reference to the frame with pageNumber
 */
FRAME *searchLRU(int pageNumber)
{
    // TODO: implement
    FRAME* currentFrame;
    currentFrame = pageTableTop;

    for(int i = 0; i < pageTableSize; i++)
    {
        // printf(" search i:%d ,currentPageNumber: %d == pageNumber %d\n",i,currentFrame->pageNumber, pageNumber);
        if( currentFrame->pageNumber == pageNumber ) // yes?
        { 
            hitIndex = i;
            return currentFrame;
        }
        currentFrame = currentFrame->under;
    }
    return NULL;
}


/* EXAMPLE of output:

USING MEMORY WITH 4 FRAMES
REFERENCE STRING: 6 1 0 7 8 0 3 1 0 3 4 1 6 8 1 0 8 6 4 1 

TESTING LRU
6 ->    6*
1 ->    1    6*
0 ->    0    1    6*
7 ->    7    0    1    6*
8 ->    8    7    0    1*
0 ->    0<   8    7    1
3 ->    3    0    8    7*
1 ->    1    3    0    8*
0 ->    0<   1    3    8
3 ->    3<   0    1    8
4 ->    4    3    0    1*
1 ->    1<   4    3    0
6 ->    6    1    4    3*
8 ->    8    6    1    4*
1 ->    1<   8    6    4
0 ->    0    1    8    6*
8 ->    8<   0    1    6
6 ->    6<   8    0    1
4 ->    4    6    8    0*
1 ->    1    4    6    8*

Number of page faults using LRU: 13

TESTING OPT
 6 ->    6*  -1   -1   -1 
 1 ->    6    1*  -1   -1 
 0 ->    6    1    0*  -1 
 7 ->    6    1    0    7*
 8 ->    6    1    0    8*
 0 ->    6    1    0<   8 
 3 ->    6    1    0    3*
 1 ->    6    1<   0    3 
 0 ->    6    1    0<   3 
 3 ->    6    1    0    3<
 4 ->    6    1    0    4*
 1 ->    6    1<   0    4 
 6 ->    6<   1    0    4 
 8 ->    6    1    0    8*
 1 ->    6    1<   0    8 
 0 ->    6    1    0<   8 
 8 ->    6    1    0    8<
 6 ->    6<   1    0    8 
 4 ->    4*   1    0    8 
 1 ->    4    1<   0    8 

Number of page faults using OPT: 9.

Quality Ratio LRU vs. OPT: 1.44
*/

void displayLRU()
{
    // TODO: implement
    FRAME* curr;
    curr = pageTableTop;
    if(hitIndex != -2)
    { // "<"
        //meaning we did not insert, just hit the pageNumber to the top.
        for(int i = 0; i < pageTableSize; i++)
        {
            if ( i == 0) {
                printf("%d<\t",curr->pageNumber);
            }else
            {    
                printf("%d\t",curr->pageNumber);   
            }
            curr = curr->under;
        }
        printf("\n");
        hitIndex = -2;
    }else
    {
        for(int i = 0; i < pageTableSize; i++)
        {
            printf("%d", curr->pageNumber);
            if( (i+1) != pageTableSize ){
                printf("\t");
            }
            curr = curr->under;
        }
        printf("*\n");
    }
    




}

void freePageTableLRU()
{
    // TODO: implement
    while(pageTableTop->under != NULL){
        pageTableTop = pageTableTop->under;
        pageTableTop->over = NULL;
        free(pageTableTop->over);
    }
    free(pageTableTop);
    free(leastRecentlyUsed); 
}

