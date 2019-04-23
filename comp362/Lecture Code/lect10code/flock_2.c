#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define oops(msg, errn)    { perror(msg); exit(errn); }

char line[256];

int main(int argc, char *argv[])
{
   int fd;
   if ((fd = open("test.txt", O_RDWR)) == -1)
      oops("Failed to open file!", 1);
   
   printf("Press <RETURN> to get file lock: ");
   getchar();
   
   printf("Trying to get file lock...\n");
   
   if (flock(fd, LOCK_EX) == -1)
      oops("fcntl", 2);
   
   printf("Got lock...\n");
   printf("Press <RETURN> to release file lock: ");
   getchar();
   
   if (flock(fd, LOCK_UN) == -1)
      oops("Failed to unlock file!", 3);
   
   printf("File unlocked.\n");
   
   close(fd);
}
