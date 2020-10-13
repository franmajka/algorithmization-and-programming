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

  long double current = 1;
  long double sum = current;
  int i = 1;
  long double q;

  do {
    q = 1. / (i * x);
    current *= q;
    sum += current;
    i++;
  } while(fabs(q) > eps);

  printf("����� ����, ����������� � ��������� %f ����� %Lf, �� ��� �������� ��������� %d. ��� ��������� e^(1/%lf) = %lf",
    eps, sum, i, x, exp(1. / x));

  return 0;
}
