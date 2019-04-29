#include  <stdio.h>
#include <stdlib.h> // for exit

#define oops(msg, errn) { perror(msg); exit(errn); }

int main(void)
{
   FILE *file_descr;
   fpos_t pos;
   char ptr[20];  /* for an existing file with 20 byte records */
   
   // open file as binary with "rb"
   file_descr = fopen("test.txt", "r");
   if (file_descr == NULL)
      oops("Could not open file", 1);
   
   // get position of file pointer
   fgetpos(file_descr, &pos);
   
   // read first record
   if (!fread(ptr,sizeof(ptr),1,file_descr))
      oops("Cannot read file", 2)
   else
      printf("1st file record: %s\n", ptr);
   
   // read second record - the value of 'pos' changes
   if (!fread(ptr,sizeof(ptr),1,file_descr))
      oops("Cannot read file", 3)
   else
      printf("2nd file record: %s\n", ptr);
   
   // reset pointer to start of file and re-read first record
   fsetpos(file_descr, &pos);
   if (!fread(ptr,sizeof(ptr),1,file_descr))
      oops("Cannot read file", 4)
   else
      printf("1st file record again: %s\n", ptr);
   
   fclose(file_descr);
}
