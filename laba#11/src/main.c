#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdbool.h>

int main() {
  system("chcp 1251");

  int length = 0;
  printf("������� ���������� �������� ��� ����� ��������� ������: ");
  scanf("%d", &length);
  length++;

  fflush(stdin);

  printf("������� �������, � ������� ������ ���������� � ����������� ����� ����� ������: ");
  char startsWith, endsWith;
  scanf("%c %c", &startsWith, &endsWith);

  fflush(stdin);

  printf("������� ������:\n");

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

  if (!counter) printf("��� �� ������ ����� ��� �������� � %c � ������������� %c", startsWith, endsWith);

  free(buffer);
  return 0;
}
