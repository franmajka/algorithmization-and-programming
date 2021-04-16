#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

int main() {
  system("chcp 1251");

  int length = 0;
  printf("Введите количество символов что будет содержать строка: ");
  scanf("%d", &length);
  length++;

  fflush(stdin);

  printf("Введите символы, с которых должно начинаться и заканчивать слово через пробел: ");
  char startsWith, endsWith;
  scanf("%c %c", &startsWith, &endsWith);

  fflush(stdin);

  printf("Введите строку:\n");

  char *buffer = (char*)malloc(length);
  fgets(buffer, length, stdin);

  char *pch = strtok(buffer, " \n");
  int counter = 0;

  while (pch != NULL) {
    if (*pch == startsWith && pch[strlen(pch) - 1] == endsWith) {
      puts(pch);
      counter++;
    }

    pch = strtok(NULL, " \n");
  }

  if (!counter) printf("Нет ни одного слова что начинает с %c и заканчивается %c", startsWith, endsWith);

  free(buffer);
  return 0;
}
