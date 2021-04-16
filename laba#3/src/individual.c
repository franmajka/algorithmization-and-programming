#include <locale.h>
#include <stdio.h>
#include <math.h>

int main() {
  setlocale(LC_ALL, "rus");

  double x;
  printf("Введите произвольное число х, такое что х != 0 и -1 < x < 1\n");
  scanf("%lf", &x);

  float eps;
  printf("Введите натуральное число эпсилон которое отвечает за точность\n");
  scanf("%f", &eps);

  if (x == 0 || x >= 1 || x <= -1 || eps <= 0) {
    printf("Некоректный ввод\n");
    return 1;
  }

  double current = 1;
  double sum = current;
  int i = 1;
  double q;

  do {
    current *= 1. / (i * x);
    sum += current;
    i++;
  } while(fabs(current) > eps);

  printf("Сумма ряда, вычисленная с точностью %f равна %lf, на это пришлось потратить %d. Для сравнения e^(1/%lf) = %lf",
    eps, sum, i, x, exp(1. / x));

  return 0;
}
