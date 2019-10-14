#include "function_v1.h"
#include "matrix_help.h"
#include "vector_help.h"
#include "math.h"

int Function(double** left, double** right, int N){

  int i, j, k;
  double g, o;

  for(i = 0; i < N; i++){

    //1) Найдем вектор отражения и запишем в первый столбец левой матрицы
//    g = scalar(get_col(left, i, N),get_col(left, i, N), i + 1, N);
    g = 0.;
    for(k = i + 1; k < N; k++){
      g = g + left[k][i] * left[k][i];
    }
    o = sqrt(g + left[i][i]*left[i][i]);
    if(o < 1e-100){
      return -1;
    }

    left[i][i] = left[i][i] - o;
    g = sqrt(g + left[i][i]*left[i][i]);

    if (g < 1e-100){
      left[i][i] = left[i][i] + o;
      continue;
    }

    
//    lineXk(left, g, i, i, N);
    for(j = i; j < N; j++){
      left[j][i] = left[j][i] / g;
    }


    //2) Умножим оставшиеся столбцы левой матрицы на вектор отражения
    for(k = i + 1; k < N; k++){
//    g = 2.0 * scalar(get_col(left, i, N),get_col(left, k, N), i, N);
      g = 0.;
      for(j = i; j < N; j++){
          g = g + left[j][i] * left[j][k];
      }
      g = 2.0 * g;
      for (j = i; j < N; j++){
        left[j][k] = left[j][k] - g * left[j][i];
      }
    }


    //3) Умножим столбцы правой матрицы на вектор отражения
    for (k = 0; k < N; k++){
//    g = 2.0 * scalar(get_col(left, i, N),get_col(right, k, N), i, N);
      g = 0.;
      for(j = i; j < N; j++){
          g = g + left[j][i] * right[j][k];
      }
      g = 2.0 * g;
      for (j = i; j < N; j++){
	      right[j][k] = right[j][k] - g * left[j][i];
      }
    }

    
    left[i][i] = o;
  }

 
  return 0;
}



int reverse_gauss(double** left, double** right, int N){
	
  int i, j, k;
  double g;

  for (k = 0; k < N; k++){
    for (i = N - 1; i >= 0; i--){
      g = right[i][k];
      for (j = i + 1; j < N; j++){
        g = g - left[i][j] * right[j][k];
      }
      right[i][k] = g / left[i][i];
    }
  }
  
  return 0;
}

    
