#include <locale.h>
#include <stdio.h>
#include <math.h>

// ������� ���������� � ������� � � �����
void swapDigits(unsigned int &n, int first, int second) {
  if (first == second) return;

  unsigned firstPower = round(pow(10, first));
  unsigned short firstDigit = (n % firstPower) / (firstPower / 10);

  unsigned secondPower = round(pow(10, second));
  unsigned short secondDigit = (n % secondPower) / (secondPower / 10);

  n -= (firstDigit * firstPower + secondDigit * secondPower) / 10;
  n += (firstDigit * secondPower + secondDigit * firstPower) / 10;
}

int main() {
  setlocale(LC_ALL, "rus");

  unsigned int n;
  printf("������� ����������� ����� n: ");
  scanf("%u", &n);

  int numLength = ceil(log10(n));
  if (n % 10 == 0) {
    numLength++;
  }

  swapDigits(n, 1, numLength);

  printf("%d", n);

  return 0;
}
