#include <locale.h>
#include <stdio.h>

int main() {
  setlocale(LC_ALL, "rus");

  float sum = 0;
  float n;

  printf("������� ������������ �����. ����� ������ ����������� �� ��� ��������� �����, ������� 0 ��� ���-��, ��� �� ���� ������.\n");

  do {
    n = 0;

    scanf("%f", &n);
    sum += n;
  } while(n);

  printf("����� ���� ��������� ����� ����� %f", sum);

  return 0;
}
