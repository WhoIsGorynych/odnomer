#include <stdio.h>
#include "matrix_help.h"
#include "vector_help.h"
#include "math.h"


//читать матрицу - первое число равно N
double** matrix_read(FILE* file, int &N){

    int i, j;
    double** matrix;


    fscanf(file, "%d", &N);
    matrix = new double*[N];
    for (i = 0; i < N; i++){
        matrix[i] = new double[N];
    }


    for(i = 0; i < N; i++){
        for(j = 0; j < N; j++){
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }


    return matrix;
}

//читать матрицу, зная N
double** matrix_read_wthtN(FILE* file, int &N){

  int i, j;
  double** matrix;
  char check;
  
  matrix = new double*[N];
  for (i = 0; i < N; i++){
    matrix[i] = new double[N];
  }

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      if(fscanf(file, "%lf", &matrix[i][j]) == 1){}
      else{
        printf("The input file is wrong!!!\n");
        N = -1;
        return matrix;
      }
    }

  }
  if(fscanf(file, "%[\n]", &check) == 1){
      if(fscanf(file, "%c", &check) == 1){
          printf("Bad symbols '%c' !!!", check);
      }
  }
  else{
    printf("Wrong size of the input file!!!\n");
    printf("%c", check);
    N = -1;
  }
  

  return matrix;
}


//enter matrix from function
double** matrix_fread(int N){

  int i, j;
  double** matrix;
  matrix = new double*[N];

  for(i = 0; i < N; i++){
    matrix[i] = new double[N];
  }

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      matrix[i][j] = 1. / (double)( i + j + 1);
    }
  }

  return matrix;
}


//печать матрицы
void matrix_print(double** matrix, int N){

    int i, j;

    for(i = 0; i < N; i++){
        printf("\n");
        for(j = 0; j < N; j++){
            printf("%lf", matrix[i][j]);
            printf(" ");
        }
    }
    printf("\n");

}




//вставить строку
void put_row(double** matrix, double* vect, int k, int N){

  int i;

  for(i = 0; i < N; i++){
    matrix[k][i] = vect[i];
  }
}



//вставить столбец
void put_col(double** matrix, double* vect, int k, int N){

  int i;

  for(i = 0; i < N; i++){
    matrix[i][k] = vect[i];
  }
}




//взять строку
double* get_row(double** matrix, int k, int N){

  int i;
  double* row;

  row = new double[N];
  for(i = 0; i < N; i++){
    row[i] = matrix[k][i];
  }

  return row;
}



//взять столбец
double* get_col(double** matrix, int k, int N){

  int i;
  double* col;

  col = new double[N];
  for(i = 0; i < N; i++){
    col[i] = matrix[i][k];
  }

  return col;
}


//взять вериткальную и горизонтальную черту
double* get_horizon(double** matrix, int k, int k1, int k2){

  int i;
  int N = k2 - k1 + 1;
  double* result;

  result = new double[N];
  for(i = 0; i < N; i++){
    result[i] = matrix[k][k1 + i];
  }

  return result;
}
double* get_vertical(double** matrix, int k, int k1, int k2){

  int i;
  int N = k2 - k1 + 1;
  double* result;

  result = new double[N];
  for(i = 0; i < N; i++){
    result[i] = matrix[k1 + i][k];
  }

  return result;
}


//вставить вертикальную и горизонтальную черту
void put_horizon(double** matrix, double* vector, int k, int k1, int k2){

  int i;
  int N = k2 - k1 + 1;

  for(i = 0; i < N; i++){
    matrix[k][k1 + i] = vector[i];
  }
}
void put_vertical(double** matrix, double* vector, int k, int k1, int k2){

  int i;
  int N = k2 - k1 + 1;

  for(i = 0; i < N; i++){
    matrix[k1 + i][k] = vector[i];
  }
}


//вставить матрицу
void put_matrix(double** matrix, double** result, int k, int N){

  int i, j;

  for(i = 0; i < N-k; i++){
    for(j = 0; j < N-k; j++){
      matrix[k+i][k+j] = result[i][j];
    }
  }
}



//взять матрицу
double** get_matrix(double** matrix, int k, int N){

  int i, j;
  double** result;

  result = new double*[N - k];
  for( i = 0; i < N-k; i++){
    result[i] = new double[N-k];
  }

  for(i = 0; i < N-k; i++){
    for(j = 0; j < N-k; j++){
      result[i][j] = matrix[k+i][k+j];
    }
  }

  return result;
}

void lineXk(double** matrix, double k, int i, int j, int N){

  double* col;

  col = get_col(matrix, i, N);
  vectXk(col, k, j, N);
  put_col(matrix, col, i, N);

}

//единичная матрица
double** identity_matrix(int N){

  double** matrix;
  int i, j;


  matrix = new double*[N];
  for (i = 0; i < N; i++){
      matrix[i] = new double[N];
      for(j = 0; j < N; j++){
          matrix[i][j] = 0.;
      }
  }


  for(i = 0; i < N; i++){
    matrix[i][i] = 1.;
  }

  return matrix;
}


double** product(double** left, double** right, int N){

  int i, j, k;
  double** result;

  result = new double*[N];
  for(i = 0; i < N; i++){
    result[i] = new double[N];
  }

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      result[i][j] = 0.;
      for(k = 0; k < N; k++){
        result[i][j] += left[i][k] * right[k][j];
      }
    }
  }

  return result;
}


double** copy(double** one, int N){

  int i, j;
  double** result;

  result = new double*[N];
  for( i = 0; i < N; i++){
    result[i] = new double[N];
  }

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      result[i][j] = one[i][j];
    }
  }

  return result;
}


double** minus(double** one, double** two, int N){
  int i, j;
  double** result;

  result = new double*[N];
  for( i = 0; i < N; i++){
    result[i] = new double[N];
  }

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      result[i][j] = one[i][j] - two[i][j];
    }
  }

  return result;
}


double error_value(double** matrix, int N){

  int i, j;
  double result = 0.;

  for(i = 0; i < N; i++){
    for(j = 0; j < N; j++){
      result = result + matrix[i][j] * matrix[i][j];
    }
  }

  return sqrt(result) / (double)N;
}
