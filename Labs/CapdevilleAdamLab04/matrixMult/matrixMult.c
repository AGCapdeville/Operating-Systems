/**
 * Name: Adam Capdeville
 * Lab/task: Lab 4
 * Date: 02/18/2019 
**/
#include "matrixMult.h"

int main(int argc, char *argv[])
{

  if (freopen(argv[1], "r", stdin) == 0)
     oops("Cannot open the input file.\n", -1);

  int **a1 = NULL, **b1 = NULL, **c1 = NULL, **a2 = NULL, **b2 = NULL, **c2 = NULL; // matrices
  int m1, k1, n1, m2, k2, n2; // dimensions of the matices m x k and k x m
 

  allocateAndLoadMatrices(&a1, &b1, &c1, &m1, &k1, &n1);
  allocateAndLoadMatrices(&a2, &b2, &c2, &m2, &k2, &n2);

  pthread_t** tids = multiply(a1,b1,c1,m1,k1,n1);
  pthread_t** tids2 = multiply(a2,b2,c2,m2,k2,n2);

  free_tids(tids,m1);
  free_tids(tids2,m2);

  // dispaly results of matrix multiplication
  printf("\nMATRIX A1\n");
  displayMatrix(a1, m1, k1);
  freeMatrix(a1, m1);
  printf("\nMATRIX B1\n");
  displayMatrix(b1, k1, n1);
  freeMatrix(b1, k1);
  printf("\nMATRIX A1 x B1\n");
  displayMatrix(c1, m1, n1);
  freeMatrix(c1, m1);


  printf("\nMATRIX A2\n");
  displayMatrix(a2, m2, k2);
  freeMatrix(a2, m2);
  printf("\nMATRIX B2\n");
  displayMatrix(b2, k2, n2);
  freeMatrix(b2, k2);
  printf("\nMATRIX A2 x B2\n");
  displayMatrix(c2, m2, n2);
  freeMatrix(c2, m2);

  return 0;
}

void *matrixThread(void *param)
{ //TODO: implement DONE
  MATRIX_CELL *cell = (MATRIX_CELL *)param;
  //DOT PRODUCT TIME
  for(int index = 0; index < (cell->k); index++ ){
    cell->c[cell->i][cell->j] += (cell->a[cell->i][index]) * (cell->b[index][cell->j]);
  }
  return NULL;
}

void allocateAndLoadMatrices(int ***a, int ***b, int ***c, int *m, int *k, int *n)
{  // TODO: implement DONE
  if (scanf("%d %d %d", m, k, n) == 0)
    oops("Cannot read matrix sizes.\n", -2);
  
  // allocate:
  allocateMatrix(a, *m, *k);
  allocateMatrix(b, *k, *n);
  allocateMatrix(c, *m, *n);


  //And Load Matrices:
  loadMatrix(a,*m,*k);
  loadMatrix(b,*k,*n);
}

void allocateMatrix(int ***matrix, int row, int col){
   *matrix = malloc( (row) * sizeof(int*));
   for( int index=0; index < row ; index++){
       (*matrix)[index] = malloc( (col) * sizeof(int) );
   }
}

void loadMatrix(int ***matrix, int m, int n)
{
  // TODO: implement DONE
   for( int row=0; row<m ; row++){
       for( int col=0; col<n ; col++){
           scanf("%d ",&(*matrix)[row][col]);
       }
   }
}

void freeMatrix(int **matrix, int m)
{
  // TODO: implement DONE
   for( int index=0; index<m ; index++){
       free(matrix[index]);
   }
   free(matrix);

}

pthread_t **multiply(int **a, int **b, int **c, int m, int k, int n)
{   // TODO: implement - DONE ?
  pthread_t **tids = alloc_tids(m, n);

  MATRIX_CELL* cell = NULL;

  for(int row = 0; row < m; row++) {
    for(int col = 0; col < n; col++) {
        cell = (MATRIX_CELL*)malloc(sizeof(MATRIX_CELL)); 
        cell->a = a;
        cell->b = b;
        cell->c = c;
        cell->i = row;
        cell->j = col;
        cell->k = k;
        pthread_create(&tids[row][col], NULL, matrixThread, (void*)cell);
    }
  }
  
  join(tids,m,n);
  
  return tids;
}

pthread_t **alloc_tids(int m, int n)
{   // TODO: implement
  pthread_t **tids;
  tids = malloc( (m) * sizeof(pthread_t*));
  for(int i =0; i < m; i++){
	  tids[i] = malloc(sizeof(pthread_t)*n);
	}
  return tids;
}

void free_tids(pthread_t **tids, int m)
{ // TODO: implement -DONE
  for(int i = 0; i < m; i++)
  {
    free(tids[i]);
  }
  free(tids); 
}

void join(pthread_t **tids, int m, int n)
{ // TODO: implement DONE
  for(int row = 0; row < m; row++){
    for(int col = 0; col < n; col++){
      pthread_join(tids[row][col], NULL);
    }
  }
}

void displayMatrix(int **matrix, int m, int n)
{
  // TODO: implement
   for( int row=0; row<m ; row++){
       for( int col=0; col<n ; col++){
           printf("%d ", matrix[row][col] );
       }
       printf("\n");
   }

}

