#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#define N 10

using namespace std;

const string SURNAMES[N] = {
  "Шевченко",
  "Смирнов",
  "Ткач",
  "Ильчук",
  "Хидео",
  "Цаль",
  "Маск",
  "Порошенко",
  "Зеленский",
  "Янукович",
};

const string PHONE_NUMBERS[N] = {
  "8(7645)193-02-33",
  "2(77)732-77-97",
  "3(1159)041-24-42",
  "869(86)841-11-80",
  "946(62)425-64-01",
  "894(0359)912-00-39",
  "750(817)745-85-37",
  "75(005)964-07-79",
  "55(8396)700-56-33",
  "1(8294)919-98-79",
};

class Record {
  private:
    string m_surname;
    string m_phoneNumber;

  public:
    Record() {
      m_surname = SURNAMES[rand() % N];
      m_phoneNumber = PHONE_NUMBERS[rand() % N];
    }

    Record(string surname, string phoneNumber) {
      m_surname = surname;
      m_phoneNumber = phoneNumber;
    }

    void print() {
      cout << m_surname << ": " << m_phoneNumber << endl;
    }

    string getSurname() {
      return m_surname;
    }

    string getPhoneNumber() {
      return m_phoneNumber;
    }
};

template <typename T>
void swapElements(T *arr, int firstPos, int secondPos) {
  T tmp = arr[firstPos];
  arr[firstPos] = arr[secondPos];
  arr[secondPos] = tmp;
}

template <typename T>
void quickSort(T *arr, bool (*compare)(T, T), int start, int end) {
  if (end - start <= 1) return;

  int pi = start;

  for (int i = start + 1; i < end; i++) {
    if (compare(arr[pi], arr[i])) continue;

    for (int j = i; j > pi; j--) {
      swapElements(arr, j, j - 1);
    }
    pi++;
  }

  quickSort(arr, compare, start, pi);
  quickSort(arr, compare, pi + 1, end);
}

template <typename T>
void quickInSort(T *arr, int length, bool (*compare)(T, T)) {
  quickSort(arr, compare, 0, length);
}

bool compareRecordsAlphabetically(Record a, Record b) {
  return a.getSurname() < b.getSurname();
}

int main() {
  system("chcp 1251");
  srand(time(NULL));

  int length = 0;
  cout << "Введите длину массива записей: ";
  cin >> length;

  Record *arr = new Record[length];

  for (int i = 0; i < length; i++) {
    arr[i].print();
  }

  cout << endl;

  string givenSurname;
  cout << "Введите фамилию, для того, чтобы заменить все записи связанные с ней на новые:" << endl;
  cin >> givenSurname;

  for (int i = 0; i < length; i++) {
    if (arr[i].getSurname() == givenSurname) {
      Record tmp;
      arr[i] = tmp;
    }
  }

  cout << endl;

  quickInSort(arr, length, compareRecordsAlphabetically);

  for (int i = 0; i < length; i++) {
    arr[i].print();
  }

  delete[] arr;
  return 0;
}
