#include <locale.h>
#include <stdio.h>
#include <math.h>
#include <malloc.h>

void printArr(double *arr, int length) {
  for (int i = 0; i < length; i++) {
    printf("%lf ", arr[i]);
  }

  printf("\n");
}

int main() {
  setlocale(LC_ALL, "rus");

  int length;
  printf("Введите длину последовательности: ");
  scanf("%d", &length);

  double *sequence = (double*)malloc(length * sizeof(double));

  sequence[0] = 0.3;
  sequence[1] = -0.3;

  for (int i = 2; i < length; i++) {
    sequence[i] = i + sin(sequence[i - 2]);
  }

  printArr(sequence, length);

  int minDiffIndex = 0;
  double minDiff = 0.3;
  double iDiff;
  for (int i = 1; i < length; i++) {
    iDiff = fabs(round(sequence[i]) - sequence[i]);
    if (iDiff < minDiff) {
      minDiffIndex = i;
      minDiff = iDiff;
    }
  }

  printf(
    "Из заданой последовательности ближайшим к целому числу является %lf. Оно отличается от целого на %lf",
    sequence[minDiffIndex],
    minDiff
  );

  free(sequence);

  return 0;
}
