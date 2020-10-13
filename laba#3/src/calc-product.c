#include <locale.h>
#include <stdio.h>
#include <math.h>

float getElement(float x) {
  return pow(x, 2) / (1 - x);
}

int main() {
  setlocale(LC_ALL, "rus");

  float res = 1;
  float n;

  printf("Вводите произвольные числа. Чтобы узнать произведение всех уже введенных чисел согласно формуле, введите 1 или что-то, что не есть числом.\n");

  while (1) {
    n = 1;

    scanf("%f", &n);
    if (n == 1) break;

    res *= getElement(n);
  };

  printf("Произведение всех введенных чисел согласно формуле равно %f", res);

  return 0;
}
