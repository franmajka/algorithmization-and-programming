#include <locale.h>
#include <stdio.h>
#include <math.h>

int main() {
  setlocale(LC_ALL, "rus");

  double x;
  printf("������� ������������ ����� �, ����� ��� � != 0 � -1 < x < 1\n");
  scanf("%lf", &x);

  float eps;
  printf("������� ����������� ����� ������� ������� �������� �� ��������\n");
  scanf("%f", &eps);

  if (x == 0 || x >= 1 || x <= -1 || eps <= 0) {
    printf("����������� ����\n");
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

  printf("����� ����, ����������� � ��������� %f ����� %lf, �� ��� �������� ��������� %d. ��� ��������� e^(1/%lf) = %lf",
    eps, sum, i, x, exp(1. / x));

  return 0;
}
