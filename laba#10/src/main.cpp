#include <iostream>
#include <clocale>
#include <ctime>
#include <cstdlib>

using namespace std;

void fillArr(int *arr, int length) {
  for (int i = 0; i < length; i++) {
    arr[i] = rand() % 201 - 100;
  }
}

void printArr(int *arr, int length) {
  for (int i = 0; i < length; i++) {
    cout << arr[i] << " ";
  }

  cout << endl;
}

void leavePositive(int *arr, int length) {
  int shift = 0;
  for (int i = 0; i < length; i++) {
    if (arr[i] > 0 && shift) {
      arr[i - shift] = arr[i];
      arr[i] = 0;
    } else {
      shift++;
      arr[i] = 0;
    }
  }
}

int main() {
  setlocale(LC_ALL, "rus");

  int length = 0;
  cout << "¬ведите длину массива: ";
  cin >> length;

  int *arr = new int[length];
  fillArr(arr, length);

  printArr(arr, length);

  leavePositive(arr, length);
  printArr(arr, length);

  delete[] arr;
  return 0;
}
