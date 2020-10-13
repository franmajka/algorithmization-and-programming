#include <stdio.h>
#include <math.h>
#include <locale.h>

unsigned int getFactorial(unsigned int n) {
  unsigned int factorial = 1;

  for (unsigned int i = 2; i <= n; i++) {
    factorial *= i;
  }

  return factorial;
}

unsigned int getCombinations(unsigned int m, unsigned int n) {
  return getFactorial(m) / (getFactorial(n) * getFactorial(m - n));
}

int main() {
  setlocale(LC_ALL, "rus");

  unsigned int m;
  unsigned int n;

  printf("¬ведите числа m и n через пробел, дл€ получени€ количества сочетаний с m по n\n");
  scanf("%u %u", &m, &n);

  printf(" оличества сочетаний с m по n равно %u", getCombinations(m, n));

  return 0;
}
