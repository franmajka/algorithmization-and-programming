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

  printf("������� ������������ �����. ����� ������ ������������ ���� ��� ��������� ����� �������� �������, ������� 1 ��� ���-��, ��� �� ���� ������.\n");

  while (1) {
    n = 1;

    scanf("%f", &n);
    if (n == 1) break;

    res *= getElement(n);
  };

  printf("������������ ���� ��������� ����� �������� ������� ����� %f", res);

  return 0;
}
