#ifndef __SIMFS_H_
#define __SIMFS_H_

// #include "defineNinclude.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <fuse.h>
#include <stdio.h>

//////////////////////////////////////////////////////////////////////////
//
// defines for the volume
//
//////////////////////////////////////////////////////////////////////////

#define SIMFS_BLOCK_SIZE 16 // 256
#define SIMFS_NUMBER_OF_BLOCKS 4096 // 65536 // 2^16
#define SIMFS_MAX_NAME_LENGTH 64 // 128
#define SIMFS_DATA_SIZE 14 // 254 // SIMFS_BLOCK_SIZE - sizeof(SIMFS_NODE_TYPE)
#define SIMFS_INDEX_SIZE 7 // 127 // two bytes => x0000 - xFFFF => 2^16 range
#define SIMFS_ROOT_NODE_INDEX 0

//////////////////////////////////////////////////////////////////////////
//
// each file/folder gets a unique identifier, and this is the initial value
// the unique identifier of the root folder will be assigned this value
//
//////////////////////////////////////////////////////////////////////////

#define SIMFS_INITIAL_VALUE_OF_THE_UNIQUE_FILE_IDENTIFIER 0

//////////////////////////////////////////////////////////////////////////
//
// defines for the in-memory data structures
//
//////////////////////////////////////////////////////////////////////////

#define SIMFS_DIRECTORY_SIZE 4099 // 65537 // prime number for the size of the directory (it is larger than 2^16)
#define SIMFS_MAX_NUMBER_OF_OPEN_FILES 64 // 1024
#define SIMFS_MAX_NUMBER_OF_PROCESSES 64 // 1024
#define SIMFS_MAX_NUMBER_OF_OPEN_FILES_PER_PROCESS 16 // 64

//////////////////////////////////////////////////////////////////////////
//
// data structures for "physical" file system
//
//////////////////////////////////////////////////////////////////////////

typedef enum {
    SIMFS_FOLDER_CONTENT_TYPE,
    SIMFS_FILE_CONTENT_TYPE,
    SIMFS_INDEX_CONTENT_TYPE,
    SIMFS_DATA_CONTENT_TYPE,
    SIMFS_INVALID_CONTENT_TYPE
} SIMFS_CONTENT_TYPE;

typedef unsigned short SIMFS_INDEX_TYPE; // is used to index blocks in the file system
#define SIMFS_INVALID_INDEX 0xFF

//
// superblock starting block in the whole file system
//
// nextUniqueIdentifier
//        is the next available value fot the unique identifier for a new folder or file
//        it is a unique very large value from [0, UINTMAX_MAX] same as [0, -1]
//        UINTMAX_MAX == 2^64 - 1 == 18,446,744,073,709,551,615
// rootNodeIndex points to the block which is the root folder of the files system
// numberOfBlock determines the size of the file system
// blockSize is the size of a single block of the file system
//
typedef union simfs_superblock_type { // size of the block with some unused part
    char spacer_dummy[SIMFS_BLOCK_SIZE]; // this makes the struct exactly one block
    struct attr {
        unsigned long long nextUniqueIdentifier; // unique identifier generator for files and folders
        SIMFS_INDEX_TYPE rootNodeIndex; // should point to the first block after the last bitvector block
        int numberOfBlocks;
        int blockSize;
    } attr;
} SIMFS_SUPERBLOCK_TYPE;

//
// file descriptor node for blocks holding folder or file information
//
//   for files:
//       te size indicates the size of the file
//       the block reference is initialized to SIMFS_INVALID_INDEX
//           - it will point to an index block when the file has content
//
//   for directories:
//       the size indicates the number of files or directories in this folder
//       the block reference points to an index block that holds references to the file and folder blocks
//
typedef char SIMFS_NAME_TYPE[SIMFS_MAX_NAME_LENGTH]; // for folder and file names

typedef struct simfs_file_descriptor_type {
    unsigned long long identifier; // unique folder/file identifier
    SIMFS_CONTENT_TYPE type; // folder or file
    SIMFS_NAME_TYPE name;  // TODO->>>>>>>>>>>>>>>>>>>>>> path name syntax question /n/m/v etc
    time_t creationTime; // creation time
    time_t lastAccessTime; // last access
    time_t lastModificationTime; // last modification
    mode_t accessRights; // access rights for the file // <<< FUSE CONTEXT
    uid_t owner; // owner ID
    size_t size; // capacity limited for this project to 2s^16
    SIMFS_INDEX_TYPE block_ref; // reference to the data or index block
} SIMFS_FILE_DESCRIPTOR_TYPE;

//
// a block for holding data
//
typedef char SIMFS_DATA_TYPE[SIMFS_DATA_SIZE];

//
// various interpretations of a file system block
//
typedef struct simfs_node_type {
    SIMFS_CONTENT_TYPE type;
    union { // content depends on the type
        SIMFS_FILE_DESCRIPTOR_TYPE fileDescriptor; // for directories and files
        SIMFS_DATA_TYPE data; // for data
        SIMFS_INDEX_TYPE index[SIMFS_INDEX_SIZE];  // for indices; all indices but the last point to data blocks
        // the last points to another index block
    } content;
} SIMFS_BLOCK_TYPE;

//
// "physical" file system structure
//
// superblock - one block
//
// bitvector - one bit per block ( (SIMFS_NUMBER_OF_BLOCKS/8 / SIMFS_BLOCK_SIZE) blocks )
//
// blocks (folder, file, data, or index) - SIMFS_NUMBER_OF_BLOCKS
//
//
typedef struct simfs_volume {
    SIMFS_SUPERBLOCK_TYPE superblock;
    unsigned char bitvector[SIMFS_NUMBER_OF_BLOCKS / 8];
    SIMFS_BLOCK_TYPE block[SIMFS_NUMBER_OF_BLOCKS];
} SIMFS_VOLUME;

//////////////////////////////////////////////////////////////////////////
//
// definitions for in-memory data structures supporting the file system
//
//////////////////////////////////////////////////////////////////////////

//
// global open file table
//
#define SIMFS_INVALID_OPEN_FILE_TABLE_INDEX -1
typedef struct simfs_open_file_global_type {
    SIMFS_CONTENT_TYPE type; // folder or file
    SIMFS_INDEX_TYPE fileDescriptor; // reference to the file descriptor node
    unsigned short referenceCount; // reference count
    time_t creationTime; // creation time
    time_t lastAccessTime; // last access
    time_t lastModificationTime; // last modification
    mode_t accessRights; // access rights for the file
    uid_t owner; // owner ID
    size_t size;
} SIMFS_OPEN_FILE_GLOBAL_TABLE_TYPE;

//
// file system directory
//
// directory entry in the conflict resolution linked list with the head in the hash table slot for
// the corresponding name
//
typedef struct simfs_dir_ent {
    // points to the "physical" file descriptor node
    SIMFS_INDEX_TYPE nodeReference;
    // a file/folder unique identifier for resolving any name hashing conflicts
    unsigned long long uniqueFileIdentifier;
    // an index to the entry for the file in the global table if file open
    // it has the value SIMFS_INVALID_OPEN_FILE_TABLE_INDEX for files that are not opened
    unsigned int globalOpenFileTableIndex;
    struct simfs_dir_ent *next;
} SIMFS_DIR_ENT;

//
// directory implemented as a hash table
//
// slots are heads to resolution lists for conflicting names
//
typedef SIMFS_DIR_ENT *SIMFS_DIRECTORY[SIMFS_DIRECTORY_SIZE];

//
// per-process open file table
//
// Note that it could be more information here for more sophisticated systems. For example, current markers
// for writing or reading would allow more complex content management of the files.
//
typedef int SIMFS_FILE_HANDLE_TYPE;
typedef struct simfs_per_process_open_file_type // a node for a local list of open files (per process)
{
    mode_t accessRights; // access rights for this process
    unsigned int globalOpenFileTableIndex; // an index to the entry for the file in the global table
} SIMFS_PER_PROCESS_OPEN_FILE_TYPE;

typedef struct simfs_process_control_block_type {
    pid_t pid; // process identifier
    int numberOfOpenFiles;
    SIMFS_INDEX_TYPE currentWorkingDirectory; // current working directory; set to the root of the volume on mounting
    SIMFS_PER_PROCESS_OPEN_FILE_TYPE openFileTable[SIMFS_MAX_NUMBER_OF_OPEN_FILES_PER_PROCESS];
    struct simfs_process_control_block_type *next;
} SIMFS_PROCESS_CONTROL_BLOCK_TYPE;

/*
 * file system context
 */
typedef struct simfs_context_type {
    SIMFS_DIRECTORY directory; // the hashtable-based in-memory directory
    unsigned char bitvector[SIMFS_NUMBER_OF_BLOCKS / 8]; // an in-memory copy of the bitvector of the simulated volume
    SIMFS_OPEN_FILE_GLOBAL_TABLE_TYPE globalOpenFileTable[SIMFS_MAX_NUMBER_OF_OPEN_FILES]; // in-memory
    SIMFS_PROCESS_CONTROL_BLOCK_TYPE *processControlBlocks;
} SIMFS_CONTEXT_TYPE;

//////////////////////////////////////////////////////////////////////////
//
// file system function declarations
//
//////////////////////////////////////////////////////////////////////////

typedef enum simfs_error {
    SIMFS_NO_ERROR,
    SIMFS_ALLOC_ERROR,
    SIMFS_DUPLICATE_ERROR,
    SIMFS_NOT_FOUND_ERROR,
    SIMFS_NOT_EMPTY_ERROR,
    SIMFS_ACCESS_ERROR,
    SIMFS_WRITE_ERROR,
    SIMFS_READ_ERROR,
    SIMFS_SYSTEM_ERROR
} SIMFS_ERROR;

SIMFS_ERROR simfsCreateFileSystem(char *simfsFileSystemName);

SIMFS_ERROR simfsUmountFileSystem(char *simfsFileSystemName);

SIMFS_ERROR simfsMountFileSystem(char *simfsFileSystemName);

SIMFS_ERROR simfsCreateFile(SIMFS_NAME_TYPE fileName, SIMFS_CONTENT_TYPE type);

SIMFS_ERROR simfsDeleteFile(SIMFS_NAME_TYPE fileName);

SIMFS_ERROR simfsGetFileInfo(SIMFS_NAME_TYPE fileName, SIMFS_FILE_DESCRIPTOR_TYPE *infoBuffer);

SIMFS_ERROR simfsOpenFile(SIMFS_NAME_TYPE fileName, SIMFS_FILE_HANDLE_TYPE *fileHandle);

SIMFS_ERROR simfsWriteFile(SIMFS_FILE_HANDLE_TYPE fileHandle, char *writeBuffer);

SIMFS_ERROR simfsReadFile(SIMFS_FILE_HANDLE_TYPE fileHandle, char **readBuffer);

SIMFS_ERROR simfsCloseFile(SIMFS_FILE_HANDLE_TYPE fileHandle);

/*
 * The following functions can be used to simulate FUSE context's user and process identifiers for testing.
 *
 * These identifiers are obtainable by calling fuse_get_context() the fuse library.
 */

struct fuse_context *simfs_debug_get_context(); // follows FUSE naming convention
char *simfsGenerateContent(int size);
unsigned long hash(unsigned char *str);
void simfsFlipBit(unsigned char *bitvector, unsigned short bitIndex);
void simfsSetBit(unsigned char *bitvector, unsigned short bitIndex);
void simfsClearBit(unsigned char *bitvector, unsigned short bitIndex);
unsigned short simfsFindFreeBlock(unsigned char *bitvector);

// CUSTOM FUNCTIONS //

SIMFS_INDEX_TYPE findNameInFolder(SIMFS_FILE_DESCRIPTOR_TYPE fd , SIMFS_NAME_TYPE fileName);

SIMFS_INDEX_TYPE findNameInIndexBlock(SIMFS_INDEX_TYPE index, SIMFS_NAME_TYPE name, int size);





#endif
