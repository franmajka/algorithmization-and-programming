#include <locale.h>
#include <stdio.h>

int main() {
  setlocale(LC_ALL, "rus");

  float min;
  float n;

  printf("������� ������������ �����. ����� ������ ����������� ����� ��������� �����, ������� 0 ��� ���-��, ��� �� ���� ������.\n");

  while (1) {
    n = 0;

    scanf("%f", &n);
    if (n == 0) break;

    min = min > n ? n : min;
  };

  printf("����������� ����� ��������� ����� ����� %f", );

  return 0;
}
