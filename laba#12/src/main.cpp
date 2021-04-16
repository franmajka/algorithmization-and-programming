#include <iostream>
#include <string>

using namespace std;

int main() {
  system("chcp 1251");

  string str;
  cout << "Введите строку:" << endl;
  getline(cin, str);

  string substr;
  cout << "Введите подстроку которую нужно заменить:" << endl;
  getline(cin, substr);

  string newSubstr;
  cout << "Введите новую подстроку:" << endl;
  getline(cin, newSubstr);

  for (char &c : str) {
    if (c != '_' && (c < 'А' || c > 'Я')) {
      cout << "Не валидная строка" << endl;
      return 1;
    }
  }

  int counter = 1;
  int si;
  while ((si = str.find(substr)) != string::npos) {
    str.replace(si, substr.length(), newSubstr + to_string(counter++));
  }

  cout << "Результат:" << endl << str;

  return 0;
}
