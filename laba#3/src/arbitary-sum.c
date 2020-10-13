#include <locale.h>
#include <stdio.h>

int main() {
  setlocale(LC_ALL, "rus");

  float sum = 0;
  float n;

  printf("Вводите произвольные числа. Чтобы узнать минимальное из уже введенных чисел, введите 0 или что-то, что не есть числом.\n");

  do {
    n = 0;

    scanf("%f", &n);
    sum += n;
  } while(n);

  printf("Сумма всех введенных чисел равна %f", sum);

  return 0;
}
