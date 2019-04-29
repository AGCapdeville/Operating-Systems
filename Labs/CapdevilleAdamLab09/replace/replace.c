/*
 *  replace.c
 *
 *  generates random sequence of page references that are fed into LRU and OPT algorithm to obtain
 *  respective numbers of page faults that are subsequently compared by calculating a ratio
 */

#include "replace.h"

int main(int argc, char *argv[])
{
    if (argc < 4)
    {
        printf("Usage: replace <num of frames> <ref string length> <upper page number bound>");
        exit(EXIT_FAILURE);
    }

    int numOfFrames = strtol(argv[1], NULL, 10);
    printf("\nUSING MEMORY WITH %d FRAMES\n", numOfFrames);

    int sizeOfRefString = strtol(argv[2], NULL, 10);
    int *referenceString = calloc(sizeOfRefString, sizeof(int));
    int range = strtol(argv[3], NULL, 10) + 1; // upper bound - 1

    // create a random page reference sequence from [0, range-1]
    srand((unsigned int) time(NULL));

    // create a random page reference sequence from [0, upper bound]
    for (int i = 0; i < sizeOfRefString; i++)
        referenceString[i] = rand() % range;

    printf("REFERENCE STRING: ");
    for (int i = 0; i < sizeOfRefString; i++)
        printf("%d ", referenceString[i]);
    printf("\n");

    printf("\nTESTING LRU\n");
    // use the LRU replacement policy to count page faults for the sequence
    int numOfFaultsLRU = testLRU(numOfFrames, referenceString, sizeOfRefString);
    printf("\nNumber of page faults using LRU: %d\n", numOfFaultsLRU);

    // use the LRU replacement policy to count page faults for the sequence
    printf("\nTESTING OPT\n");
    int numOfFaultsOPT = testOPT(numOfFrames, referenceString, sizeOfRefString);
    printf("\nNumber of page faults using OPT: %d.\n", numOfFaultsOPT);

    printf("\nQuality Ratio LRU vs. OPT: %.2f\n", (double) numOfFaultsLRU / (double) numOfFaultsOPT);

    exit(EXIT_SUCCESS);
}
