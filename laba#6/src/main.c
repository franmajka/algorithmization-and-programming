#include <locale.h>
#include <stdio.h>
#include <math.h>

// »ндексы начинаютс€ с единицы и с конца
void swapDigits(unsigned *n, unsigned first, unsigned second) {
  if (first == second) return;

  unsigned firstPower = round(pow(10, first));
  unsigned short firstDigit = (*n % firstPower) / (firstPower / 10);

  unsigned secondPower = round(pow(10, second));
  unsigned short secondDigit = (*n % secondPower) / (secondPower / 10);

  *n -= (firstDigit * firstPower + secondDigit * secondPower) / 10;
  *n += (firstDigit * secondPower + secondDigit * firstPower) / 10;
}

int main() {
  setlocale(LC_ALL, "rus");

  unsigned n;
  printf("¬ведите натуральное число n: ");
  scanf("%u", &n);

  int numLength = (int)(log10(n)) + 1;

  swapDigits(&n, 1, numLength);

  printf("%d", n);

  return 0;
}
