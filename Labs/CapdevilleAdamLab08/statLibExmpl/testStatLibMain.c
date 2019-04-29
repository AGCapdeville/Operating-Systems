/*
 *  testStatLibMain.c
 *  lect09
 *
 *  Created by AJ Bieszczad on 3/16/09.
 *  Copyright 2009 CSUCI. All rights reserved.
 *
 *
 */

#include <stdio.h>

extern int giveMeNum();

int main(int argc, char **argv)
{
   printf ("You gave me : %d\n", giveMeNum());
   return 0;
}
