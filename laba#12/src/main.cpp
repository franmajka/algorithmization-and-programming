#include <iostream>
#include <string>

using namespace std;

int main() {
  system("chcp 1251");

  string str;
  cout << "������� ������:" << endl;
  getline(cin, str);

  string substr;
  cout << "������� ��������� ������� ����� ��������:" << endl;
  getline(cin, substr);

  string newSubstr;
  cout << "������� ����� ���������:" << endl;
  getline(cin, newSubstr);

  for (char &c : str) {
    if (c != '_' && (c < '�' || c > '�')) {
      cout << "�� �������� ������" << endl;
      return 1;
    }
  }

  int counter = 1;
  int si;
  while ((si = str.find(substr)) != string::npos) {
    str.replace(si, substr.length(), newSubstr + to_string(counter++));
  }

  cout << "���������:" << endl << str;

  return 0;
}
