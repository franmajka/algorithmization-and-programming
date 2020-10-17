#include <locale.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>

void printArr(int *arr, int length) {
  for (int i = 0; i < length; i++) {
    printf("%d ", arr[i]);
  }

  printf("\n");
}

int* shuffle(int *arr, int length){
  int *shuffled = (int*)malloc(sizeof(int) * length);

  for (int i = 0, j = 0; i < length / 2; i++, j += 2) {
    shuffled[j] = arr[i];
  }

  for (int i = length - 1, j = 1; i >= length / 2; i--, j += 2) {
    shuffled[j] = arr[i];
  }

  return shuffled;
}

int main() {
  setlocale(LC_ALL, "rus");

  srand(time(NULL));

  int length;
  printf("¬ведите размер последовательности (парное число): ");
  scanf("%d", &length);

  if (length % 2 != 0) {
    printf("Ќекорректный размер последовательности");
    return 1;
  }

  int *sequence = (int*)malloc(sizeof(int) * length);
  for (int i = 0; i < length; i++) {
    sequence[i] = rand() % 10;
  }

  printf("—лучайна€ последовательность длинной в %d элементов:\n", length);
  printArr(sequence, length);

  sequence = shuffle(sequence, length);
  printf("Ёта же последовательность, но перемешанна€ согласно условию:\n");
  printArr(sequence, length);

  free(sequence);

  return 0;
}
