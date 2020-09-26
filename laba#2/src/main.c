#include <stdio.h>
#include <locale.h>
#include <math.h>

// ������ ��-�������� ��������� a � b ��� ����� ��������� �� � �� ���� ��� ��� �������� � C
double getY(double a, double b, double x) {
  if (x == 0) {
    return 0;
  } else if (x > 1) {
    return pow(a * M_E, -b * x) * cos(x * M_PI);
  } else {
    return pow(x - 5, 2) * pow(pow(x + 1, 2), 1. / 3.);
  }
}

int main() {
  setlocale(LC_ALL, "rus");

  double a;
  double b;
  double start;
  double end;
  double step;

  printf("������� ����� a � b ����� ������: ");
  scanf("%lf %lf", &a, &b);

  printf("������� ����� � ������� �� - �� ���: ");
  scanf("%lf - %lf %lf", &start, &end, &step);

  for (double x = start; x <= end; x += step) {
    printf("\n��� x = %lf, y = %lf", x, getY(a, b, x));
  }

  return 0;
}
