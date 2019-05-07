#include "disk.h"

disk_t disk;


int log2phys(int logaddr, physaddr_t *phaddr)
{
    // TODO: implement
    if(logaddr > MAX_LOGICAL_SECTOR || logaddr < 0){
        return SIM_DEV_ERROR; // invalid logical address!
    }

    //EX: Logaddr: 200000
    phaddr->cyl = logaddr / (NUM_OF_HEADS * NUM_OF_SECTS); // Cylinder Index  :floor(156.25)
    phaddr->head = logaddr % (NUM_OF_HEADS * NUM_OF_SECTS) / NUM_OF_SECTS; // Index of Head :floor(2.5)
    // phaddr->sect = logaddr % (NUM_OF_SECTS); // Index in Head ... not sure if +1
    phaddr->sect = ((logaddr % (NUM_OF_HEADS * NUM_OF_SECTS)) % NUM_OF_SECTS)+1;
    return SIM_DEV_SUCCESS;
}

int phys2log(physaddr_t *phaddr)
{
    // TODO: implement
    // Assuming correct input
    return (phaddr->cyl * NUM_OF_HEADS * NUM_OF_SECTS) + 
           (phaddr->head * NUM_OF_SECTS) + 
           (phaddr->sect) - 1;
}

void printTransl(int logaddr)
{
    physaddr_t phaddr;

    printf("Logical sector number: %d\n", logaddr);
    if (log2phys(logaddr, &phaddr) == 0)
    {
        printf("Physical address: (%d, %d, %d)\n", phaddr.cyl, phaddr.head, phaddr.sect);

        if (phys2log(&phaddr) != logaddr)
            printf("ERROR: no match!\n");
    } else
        printf("ERROR: invalid logical address!\n");
}

int invalidParameters(int log_block_num, int numBlock)
{
    if (log_block_num < 0)
        return SIM_DEV_ERROR;
    if (numBlock < 0)
        return SIM_DEV_ERROR;
    if (log_block_num + numBlock >= MAX_LOGICAL_SECTOR)
        return SIM_DEV_ERROR;
    return SIM_DEV_SUCCESS;
}

int readDisk(int logical_block_num, int numOfBlocks, void **buffer)
{
    // TODO: implement
    printf("\tREAD \n");
    // we break here for a read and not a write
    if (invalidParameters(logical_block_num, numOfBlocks))
        return SIM_DEV_ERROR;
    
    if (numOfBlocks == 0)
        return SIM_DEV_SUCCESS;

    physaddr_t tempaddr;
    char * buf = buffer;

    for (int i = 0; i < numOfBlocks; i++)
    {
        log2phys(logical_block_num+i, &tempaddr); // -i
        memcpy(&buf[i*SECT_SIZE], disk[tempaddr.cyl][tempaddr.head][tempaddr.sect], SECT_SIZE);
    }
    return SIM_DEV_SUCCESS;
}

int writeDisk(int logicalBlockNum, int numOfSectors, void *buffer)
{
    // TODO: implement 
    printf("\tWRITE \n");
    if (invalidParameters(logicalBlockNum, numOfSectors))
        return SIM_DEV_ERROR;
    if (numOfSectors == 0)
        return SIM_DEV_SUCCESS;
    physaddr_t tempaddr;
    char * buf = buffer;

    for(int i = 0; i < numOfSectors; i++)
    {   
        log2phys(logicalBlockNum+i, &tempaddr);
        memcpy(disk[tempaddr.cyl][tempaddr.head][tempaddr.sect], &buf[i*SECT_SIZE], SECT_SIZE);
    }

    return SIM_DEV_SUCCESS;
}

//TODO: for task 2, random content:
void simfsGenerateContent(int size, char* buffer)
{
    size = (size <= 0 ? rand() % SECT_SIZE : SECT_SIZE*8); // arbitrarily chosen as an example
    int firstPrintable = ' ';
    int len = '~' - firstPrintable;
    
    for (int i = 0; i < size - 1; i++)
        *(buffer + i) = firstPrintable + rand() % len;

    buffer[size - 1] = '\0';
}

int main(int argc, char *argv[])
{
    // TODO: extend to also test for reading and writing

    physaddr_t phaddr;
    char inputBuffer[8*SECT_SIZE];
    char outputBuffer[8*SECT_SIZE];

    memset(inputBuffer,'\0',8*SECT_SIZE);
    memset(outputBuffer,'\0', 8*SECT_SIZE);

    char randomContent[8*SECT_SIZE];
    simfsGenerateContent(8*SECT_SIZE,randomContent);

    int logaddr;
    int test = 10;

    if (argc < 2)
        while (test != 0)
        {
            logaddr = rand() % MAX_LOGICAL_SECTOR;
            printTransl(logaddr);
            int rng = rand()%8;
            if(rng != 0){
                memset(inputBuffer, '\0', 8*SECT_SIZE);
                memset(outputBuffer,'\0', 8*SECT_SIZE);

                memcpy(inputBuffer, randomContent, rng*SECT_SIZE);
                writeDisk(logaddr, rng, inputBuffer);
                printf(" INPUT:\n%s \n\n",inputBuffer);
                readDisk(logaddr, rng, (void *) &outputBuffer);
                printf("OUTPUT:\n%s \n\n", outputBuffer);            

                printf("Input length: %lu\n", strlen(inputBuffer));
                printf("Retrieved length: %lu\n", strlen(outputBuffer));
                if(strcmp(inputBuffer,outputBuffer) == 0){
                    printf("inputBuffer == outputBuffer, meaning writing and reading works \n");
                }
                test--;
            }else
            {
                printf("Input is zero so no need to write & read \n");
            }
            printf("\n\n");
            usleep(1000000);
        }
    // switch (argv[1][0]) // "l" for logical "p" for physical
        // {
        //     case 'l': // logical
        //         if (argv[2] == NULL)
        //             break;
        //         logaddr = strtol(argv[2], NULL, 10) % MAX_LOGICAL_SECTOR;
        //         printTransl(logaddr);
        //         break;

        //     case 'p': // physical
        //         if (argv[2] == NULL || argv[3] == NULL || argv[4] == NULL)
        //             break;
        //         phaddr.cyl = strtol(argv[2], NULL, 10);
        //         phaddr.head = strtol(argv[3], NULL, 10);
        //         phaddr.sect = strtol(argv[4], NULL, 10);
        //         logaddr = phys2log(&phaddr);
        //         printTransl(logaddr);
        //         break;
        // }
}
