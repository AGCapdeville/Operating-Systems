#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define oops(msg, errn)    { perror(msg); exit(errn); }

char line[256];

int main(int argc, char *argv[])
{
   struct flock filelock;
   filelock.l_type   = F_WRLCK;  /* F_RDLCK, F_WRLCK, F_UNLCK    */
   filelock.l_whence = SEEK_SET; /* SEEK_SET, SEEK_CUR, SEEK_END */
   filelock.l_start  = 0;        /* Offset from l_whence         */
   filelock.l_len    = 0;        /* length, 0 = to EOF           */
   filelock.l_pid    = getpid(); /* our PID                      */
   
   if (argc > 1)
      filelock.l_type = F_RDLCK;
   
   int fd;
   if ((fd = open("test.txt", O_RDWR)) == -1)
      oops("Failed to open file!", 1);
   
   printf("Press <RETURN> to get file lock: ");
   getchar();
   
   printf("Trying to get file lock...\n");
   
   if (fcntl(fd, F_SETLK, &filelock) == -1)
      oops("fcntl", 2);
   
   printf("Got lock...\n");
   printf("Press <RETURN> to release file lock: ");
   getchar();
   
   filelock.l_type = F_UNLCK;
   
   if (fcntl(fd, F_SETLK, &filelock) == -1)
      oops("Failed to unlock file!", 3);
   
   printf("File unlocked.\n");
   
   close(fd);
}
