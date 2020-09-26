#include <math.h>
#include <stdio.h>
#include <locale.h>

double getX(double a, double b, double c) {
  return pow(b, a + 1) / pow(fabs(b - c), 1. / 3.) + (a + b / 2.) / (2. * fabs(a + b));
}

double getY(double a) {
  return pow(a + 1, -1 / sin(a));
}

int main(void) {
  setlocale(LC_ALL, "rus");

  double a;
  double b;
  double c;

  printf("¬ведите числа a, b и c через пробел: ");
  scanf("%lf %lf %lf", &a, &b, &c);

  printf("x = %lf; y = %lf", getX(a, b, c), getY(a));

  return 0;
}
