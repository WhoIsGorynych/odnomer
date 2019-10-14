#include <stdio.h>
#include "matrix_help.h"
#include <iostream>
#include <stdlib.h>
#include "function_v1.h"
#include <time.h>


int main(int argc, char** argv){

//  int i;
  int N;
  double **matrix_old;
  double **matrix_check;
  double **matrix_new;

  if(argc == 1){
    printf("Not enough arguments!!!\n");
    return -1;
  }
  else if(argc == 2){
    N = atoi(argv[1]);
    matrix_old = matrix_fread(N);
  }
  else if(argc == 3){
      N = atoi(argv[1]);
      FILE* file = fopen(argv[2], "r");
      if(file == NULL){
          printf("No file was found!!!\n");
          return -1;
      }
      matrix_old = matrix_read_wthtN(file, N);
  }
  else{
      printf("Too many arguments!!!\n");
      return -1;
  }

  
// check matrix_old
  if( N == -1){
      return -1;
  }
  
//Input values
  printf("\n\nInput values: \n");
  printf("N = %d\n", N);
  printf("Matrix:");
//  matrix_print(matrix_old, N);
  matrix_new = identity_matrix(N);
  matrix_check = copy(matrix_old, N);



  clock_t start = clock();

//Main process
  Function(matrix_old, matrix_new, N);
  clock_t end = clock();
//Reverse Gauss
  reverse_gauss(matrix_old, matrix_new, N);

//  clock_t end = clock();
  double seconds = (double)(end - start) / CLOCKS_PER_SEC;
  printf("\nIt took %lf seconds\n", seconds);



//Answerr
//  printf("\nAnswer:");
//  matrix_print(matrix_new, N);

//Check
//  printf("\nCheck: ");
//  matrix_print(product(matrix_new, matrix_check, N), N);

//Error
  printf("\n||A * A^(-1) - E|| = ");
  printf("%lf", error_value(minus(product(matrix_new, matrix_check, N), identity_matrix(N), N), N));
  printf("\n");

  delete[] matrix_old;
  delete[] matrix_new;
  delete[] matrix_check;

}
