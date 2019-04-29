/*
 *  dir.c
 *
 *  Created by AJ Bieszczad on 4/14/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 */

#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdlib.h> // for exit

#define oops(msg, errn) { perror(msg); exit(errn); }

int main(int argc, char *argv[])
{
   DIR *dir;
   struct dirent *dir_entry;
   
   if ((dir = opendir(".")) == NULL)
      oops("Cannot open the directory.", 1);

   printf("DIRECTORY LISTING:\n");
   while ((dir_entry = readdir(dir)) != NULL)
   {
      printf("%-6s %s\n", "Name:", dir_entry->d_name);
      printf("%-7s", "Type:");
      switch(dir_entry->d_type)
      {
         default:
         case DT_UNKNOWN:
            printf("UNKNOWN\n");
            break;
         case DT_FIFO:
            printf("FIFO\n");
            break;
         case DT_CHR:
            printf("DT_CHR\n");
            break;
         case DT_DIR:
            printf("DT_DIR\n");
            break;
         case DT_BLK:
            printf("DT_BLK\n");
            break;
         case DT_REG:
            printf("DT_REG\n");
            break;
         case DT_LNK:
            printf("DT_LNK\n");
            break;
         case DT_SOCK:
            printf("DT_SOCK\n");
            break;
         case DT_WHT:
            printf("DT_WHT\n");
            break;
      }
   }
   
   closedir(dir);
}
