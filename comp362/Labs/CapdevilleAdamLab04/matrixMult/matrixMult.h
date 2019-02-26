/**
 * Name: Adam Capdeville
 * Lab/task: Lab 4
 * Date: 02/18/2019 
**/
#ifndef __MATRIX_MULT_H_
#define __MATRIX_MULT_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define oops(errmsg, err) { perror(errmsg); exit(err); }

// struct for passing indices to the threads
typedef struct matrixCell
{
   int i;
   int j;
   int k;
   int **a;
   int **b;
   int **c;
} MATRIX_CELL;

void *matrixThread(void *);
void allocateAndLoadMatrices(int ** *, int ** *, int ** *, int *, int *, int *);
void loadMatrix(int ** *, int, int);
void allocateMatrix(int ** *, int, int);
void freeMatrix(int **, int);
pthread_t **alloc_tids(int, int);
void free_tids(pthread_t **, int);
pthread_t **multiply(int **, int **, int **, int, int, int);
void join(pthread_t **, int, int);
void displayMatrix(int **, int, int);

#endif
