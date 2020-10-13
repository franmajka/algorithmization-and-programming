#include <locale.h>
#include <stdio.h>

int main() {
  setlocale(LC_ALL, "rus");

  float min;
  float n;

  printf("Вводите произвольные числа. Чтобы узнать минимальное среди введенных чисел, введите 0 или что-то, что не есть числом.\n");

  while (1) {
    n = 0;

    scanf("%f", &n);
    if (n == 0) break;

    min = min > n ? n : min;
  };

  printf("Минимальное среди введенных чисел равно %f", );

  return 0;
}
