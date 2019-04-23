/**
 * Name: Adam Capdeville
 * PROJECT 1
 * Date: 04/22/2019 
**/

#include "simfs.h"

#define SIMFS_FILE_NAME "simfsFile.dta"

SIMFS_ERROR PrintError(SIMFS_ERROR error) {
    if (error == SIMFS_NO_ERROR)
        return error;
    
    printf("Error: ");
    switch(error) {
        case SIMFS_NO_ERROR:
            printf("SIMFS_NO_ERROR\n");
            break;
        case SIMFS_ALLOC_ERROR: 
            printf("SIMFS_ALLOC_ERROR\n"); 
            break;
        case SIMFS_DUPLICATE_ERROR: 
            printf("SIMFS_DUPLICATE_ERROR\n"); 
            break;
        case SIMFS_NOT_FOUND_ERROR: 
            printf("SIMFS_NOT_FOUND_ERROR\n"); 
            break;
        case SIMFS_NOT_EMPTY_ERROR: 
            printf("SIMFS_NOT_EMPTY_ERROR\n"); 
            break;
        case SIMFS_ACCESS_ERROR: 
            printf("SIMFS_ACCESS_ERROR\n"); 
            break;
        case SIMFS_WRITE_ERROR: 
            printf("SIMFS_WRITE_ERROR\n"); 
            break;
        case SIMFS_READ_ERROR: 
            printf("SIMFS_READ_ERROR\n"); 
            break;
        case SIMFS_SYSTEM_ERROR: 
            printf("SIMFS_SYSTEM_ERROR\n"); 
            break;
        default:
            printf("Unkonwn\n");
    }
    return error;
}




SIMFS_ERROR testTask1()
{
    srand(1990);

    PrintError(simfsCreateFileSystem(SIMFS_FILE_NAME));
    PrintError(simfsMountFileSystem(SIMFS_FILE_NAME));

    // (SIMFS_NAME_TYPE fileName, SIMFS_CONTENT_TYPE type)
    SIMFS_NAME_TYPE newFile = "file1"; // type = file;
   
    printf("\nADD \"file1\" \n");
    PrintError(simfsCreateFile(newFile, SIMFS_FILE_CONTENT_TYPE));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());

    SIMFS_FILE_DESCRIPTOR_TYPE info[1];
    strcpy(info->name, "null");
    PrintError(simfsGetFileInfo(newFile, info));
        time_t t = info->creationTime;
        struct tm *tmp = gmtime(&t);
    printf("\n  FETCH FILE INFO: \n   name: %s,\n   creationTime: %d:%d:%d \n", info->name, tmp->tm_hour, tmp->tm_min, tmp->tm_sec);

    printf("\nADD \"file2\" \n");
    strcpy(newFile, "file2");
    PrintError(simfsCreateFile(newFile, SIMFS_FILE_CONTENT_TYPE));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());
    

    printf("\nADD \"file2\" \n");
    strcpy(newFile, "file2");
    PrintError(simfsCreateFile(newFile, SIMFS_FILE_CONTENT_TYPE));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());

    printf("\nDELETE \"file2\" \n");
    PrintError(simfsDeleteFile(newFile));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());

   
    printf("\nADD \"file2\" \n");
    strcpy(newFile, "file2");
    PrintError(simfsCreateFile(newFile, SIMFS_FILE_CONTENT_TYPE));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());


    printf("\nADD \"folder1\" \n");
    strcpy(newFile, "folder1");
    PrintError(simfsCreateFile(newFile, SIMFS_FOLDER_CONTENT_TYPE));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());


    return EXIT_SUCCESS;
}

SIMFS_ERROR testTask2()
{
    srand(1990);

    unsigned long long test = UINTMAX_MAX;
    printf("MAX unique identifier: %llu\n", test);
    
    // CREATE SYSTEM
    printf("CREAT & MOUNT FILE SYSTEM\n");
    if (simfsCreateFileSystem(SIMFS_FILE_NAME) != SIMFS_NO_ERROR)
        exit(EXIT_FAILURE);
    // TEST MOUNT SYSTEM
    if (simfsMountFileSystem(SIMFS_FILE_NAME) != SIMFS_NO_ERROR){
        printf("MOUNT: FAILED\n");
        exit(EXIT_FAILURE);
    }else
    {
        printf("MOUNT: SUCCEDED\n");
    }

    SIMFS_NAME_TYPE newFile = "file1"; // type = file;
    printf("\nADD \"file1\" \n");
    PrintError(simfsCreateFile(newFile, SIMFS_FILE_CONTENT_TYPE));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());

    printf("\nADD \"file2\" \n");
    strcpy(newFile, "file2");
    PrintError(simfsCreateFile(newFile, SIMFS_FILE_CONTENT_TYPE));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());

    printf("\nADD \"file2\" \n");
    strcpy(newFile, "file2");
    PrintError(simfsCreateFile(newFile, SIMFS_FILE_CONTENT_TYPE));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());

    printf("\nDELETE \"file2\" \n");
    PrintError(simfsDeleteFile(newFile));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());

    printf("\nADD \"file2\" \n");
    strcpy(newFile, "file2");
    PrintError(simfsCreateFile(newFile, SIMFS_FILE_CONTENT_TYPE));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());

    printf("\nADD \"folder1\" \n");
    strcpy(newFile, "folder1");
    PrintError(simfsCreateFile(newFile, SIMFS_FOLDER_CONTENT_TYPE));
    printf("\n\tSZE OF CWD: %d\n", getSizeOfSIMFS());

    // TEST MOUNT & UNMOUNT 
    
    // UNMOUNT
    printf("\tTEST MOUNT -> UNMOUNT -> MOUNT :\n");
    if (simfsUmountFileSystem(SIMFS_FILE_NAME) != SIMFS_NO_ERROR){
        printf("\t  UNMOUNT: FAILED\n");
        exit(EXIT_FAILURE);
    }else
    {    
        printf("\t  UNMOUNT: SUCCEDED\n"); 
    }
    // MOUNT
    if (simfsMountFileSystem(SIMFS_FILE_NAME) != SIMFS_NO_ERROR){
        printf("\t  MOUNT: FAILED\n");
        exit(EXIT_FAILURE);
    }else
    {
        printf("\t  MOUNT: SUCCEDED\n");
    }
    // UNMOUNT
    if (simfsUmountFileSystem(SIMFS_FILE_NAME) != SIMFS_NO_ERROR){
        printf("\t  UNMOUNT: FAILED\n");
        exit(EXIT_FAILURE);
    }else
    {    
        printf("\t  UNMOUNT: SUCCEDED\n"); 
    }

    return EXIT_SUCCESS;
}




int main()
{
//    srand(time(NULL)); // uncomment to get true random values in get_context()

    unsigned long long test = UINTMAX_MAX;
    printf("MAX unique identifier: %llu\n", test);

    // TODO: implement thorough testing of all the functionality
    printf("\n\n-- TASK 1 START --\n");
    PrintError(testTask1());
    printf("\n-- TASK 1 DONE --\n");


    printf("\n\n-- TASK 2 START--\n");
    PrintError(testTask2());
    printf("\n-- TASK 2 DONE--\n");


    // the following is just some sample code for simulating user and process identifiers that are
    // needed in the simfs functions
        int count = 10;
        char *content;
        struct fuse_context *context;
        for (int i = 0; i < count; i++)
        {
            context = simfs_debug_get_context();
            printf("user ID = %02i, process ID = %02i, group ID = %02i, umask = %04o\n",
                   context->uid, context->pid, context->gid, context->umask);
            content = simfsGenerateContent(i * 10);
            //printf("content = \"%s\"\nhash(content) = %ld\n", content, hash((unsigned char *) content) );
        }


    unsigned char testBitVector[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
    simfsFlipBit(testBitVector, 44);
    printf("Found free block at %d\n", simfsFindFreeBlock(testBitVector));
    simfsClearBit(testBitVector, 33);
    printf("Found free block at %d\n", simfsFindFreeBlock(testBitVector));
    simfsSetBit(testBitVector, 33);
    printf("Found free block at %d\n", simfsFindFreeBlock(testBitVector));

    return EXIT_SUCCESS;
}
