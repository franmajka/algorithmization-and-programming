#include <locale.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>

void fillWithRandom(int *arr, int length) {
  for (int i = 0; i < length; i++) {
    arr[i] = rand() % 41 - 20;
  }
}

void printArr(int *arr, int length) {
  for (int i = 0; i < length; i++) {
    printf("%d ", arr[i]);
  }

  printf("\n");
}

void copyArray(int *arrCopyTo, int *arrCopyFrom, int length) {
  for (int i = 0; i < length; i++) {
    arrCopyTo[i] = arrCopyFrom[i];
  }
}

void shuffle(int *arr, int length){
  int *shuffled = (int*)malloc(sizeof(int) * length);

  for (int i = 0, j = 0; i < length / 2; i++, j += 2) {
    shuffled[j] = arr[i];
  }

  for (int i = length - 1, j = 1; i >= length / 2; i--, j += 2) {
    shuffled[j] = arr[i];
  }

  copyArray(arr, shuffled, length);

  free(shuffled);
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
  fillWithRandom(sequence, length);

  printf("—лучайна€ последовательность длинной в %d элементов:\n", length);
  printArr(sequence, length);

  shuffle(sequence, length);
  printf("Ёта же последовательность, но перемешанна€ согласно условию:\n");
  printArr(sequence, length);

  free(sequence);

  return 0;
}
