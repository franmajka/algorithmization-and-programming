#include <locale.h>
#include <stdio.h>
#include <malloc.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

int **initSquareMatrix(int N) {
  int **matrix = (int**)malloc(N * sizeof(int));
  for (int i = 0; i < N; i++) {
    matrix[i] = (int*)malloc(N * sizeof(int));
    for (int j = 0; j < N; j++) {
      matrix[i][j] = (rand() % 199) - 99; // [-99 ; 99]
    }
  }

  return matrix;
}

void printSquareMatrix(int **matrix, int N) {
  printf("\n");

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      printf("%3d\t", matrix[i][j]);
    }
    printf("\n");
  }

  printf("\n");
}

void swapCols(int **matrix, int N, int first, int second) {
  int temp;
  for (int i = 0; i < N; i++) {
    temp = matrix[i][first];
    matrix[i][first] = matrix[i][second];
    matrix[i][second] = temp;
  }
}

void freeSquareMatrix(int **matrix, int N) {
  for (int i = 0; i < N; i++) {
    free(matrix[i]);
  }
  free(matrix);
}

int main() {
  setlocale(LC_ALL, "rus");
  srand(time(NULL));

  int N;
  printf("Введите число N, которое отвечает за количество столбцов и строк в матрице: ");
  scanf("%d", &N);

  int **A = initSquareMatrix(N);

  printSquareMatrix(A, N);

  int K;
  printf("Введите число K, которое отвечает за столбцы, которые будут сменены местами: ");
  scanf("%d", &K);

  K--;

  if (K >= N || K < 0) {
    printf("Некорректное число К");
    return 1;
  }

  int maxCol = 0;
  for (int j = 1; j < N; j++) {
    if (fabs(A[K][maxCol]) < fabs(A[K][j])) {
      maxCol = j;
    }
  }

  swapCols(A, N, maxCol, K);

  printSquareMatrix(A, N);
  printf("Столбцы %d и %d поменялись местами", K + 1, maxCol + 1);

  freeSquareMatrix(A, N);

  return 0;
}
