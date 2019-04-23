/*
 *  fstats.c
 *  flock
 *
 *  Created by AJ Bieszczad on 4/13/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

#define oops(msg, errn)    { perror(msg); exit(errn); }

#define fileName    "test.txt"

int main(int argc, char *argv[])
{
    struct stat fileInfo;
    if (stat(".", &fileInfo) < 0)
        oops("Cannot stat the file.", 1);

    printf("FILE INFO: %s\n\n", fileName);
    printf("%-37s %12s = %10u\n", "Device inode resides on", "st_dev", (int) fileInfo.st_dev);
    printf("%-37s %12s = %10d\n", "Inode's number", "st_ino", (int) fileInfo.st_ino);
    printf("%-37s %12s = %10d\n", "Inode protection mode", "st_mode", (int) fileInfo.st_mode);
    printf("%-37s %12s = %10d\n", "Number or hard links to the file", "st_nlink", (int) fileInfo.st_nlink);
    printf("%-37s %12s = %10d\n", "User-id of owner", "st_uid", (int) fileInfo.st_uid);
    printf("%-37s %12s = %10d\n", "Group-id of owner", "st_gid", (int) fileInfo.st_gid);
    printf("%-37s %12s = %10d\n", "Device type, for special file inode", "st_rdev", (int) fileInfo.st_rdev);
#ifdef __APPLE__
    printf("%-37s %12s = %10d\n", "Time since last access", "st_atimespec", (int) fileInfo.st_atimespec.tv_sec);
    printf("%-37s %12s = %10d\n", "Time since last data modification", "st_mtimespec", (int) fileInfo.st_mtimespec.tv_sec);
    printf("%-37s %12s = %10d\n", "Time since last file status change", "st_ctimespec", (int) fileInfo.st_ctimespec.tv_sec);
#else
    printf("%-37s %12s = %10d\n", "Time since last access", "st_atimespec", (int) fileInfo.st_atime);
    printf("%-37s %12s = %10d\n", "Time since last data modification", "st_mtimespec", (int) fileInfo.st_mtime);
    printf("%-37s %12s = %10d\n", "Time since last file status change", "st_ctimespec", (int) fileInfo.st_ctime);
#endif
    printf("%-37s %12s = %10d\n", "File size, in bytes", "st_size", (int) fileInfo.st_size);
    printf("%-37s %12s = %10d\n", "Blocks allocated for file", "st_blocks", (int) fileInfo.st_blocks);
    printf("%-37s %12s = %10d\n", "Optimal file sys I/O ops blocksize", "st_blksize", (int) fileInfo.st_blksize);
#ifdef __APPLE__
    printf("%-37s %12s = %10o\n", "User defined flags for file", "st_flags", (int) fileInfo.st_flags);
    printf("%-37s %12s = %10d\n", "File generation number", "st_gen", (int) fileInfo.st_gen);
#endif
}
