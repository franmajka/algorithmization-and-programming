// ���� ����� ��-02
// https://www.onlinegdb.com/online_c++_compiler

#include <iostream>
#include <string>

using namespace std;

// ������� ������������ ����� ����� � ������
int getLongestWord(const string& str) {
    // �� ��������� ����� ��� �� ��������
    // ���������� ���� ����� "auto wordBegin" �� �� � ���� ���
    string::const_iterator wordBegin = str.end();
    int maxLength = -1;

    // ���������� �� ���� �������� ������
    for (string::const_iterator it = str.begin();; ++it) {
        // ���� �� ����� �� ����� �����
        if ((*it == ' ' || it == str.end()) && wordBegin != str.end()) {
            // ��������� ��� ����� ��� ����� ����� �����������
            // ����� ���� ������� ��� ������� �������
            int wordLength = distance(wordBegin, it);

            // ���� ����� �������� ����� ������ ����������� �������� ����
            if (wordLength > maxLength) maxLength = wordLength;

            // ��� ��� ����� ������ ����� ���� ����� ������ �����
            // �� �� ���������� ���������� ��������� ��� ����� for
            // � ������ ������ break
            if (it == str.end()) break;

            // �������� ������ �����
            wordBegin = str.end();

            continue;
        }

        if (it == str.end()) break;

        // ������ ������ �����
        // �� �������� ��� ����� ������ �������� �� ���
        // ���������� ������� � ������� ������-�� regex
        // �� � �� ����� �������� ��� ��� ��� ���
        // \n \r \0 ��������� �������� ������
        if (*it != ' ' && wordBegin == str.end()) {
            wordBegin = it;
            continue;
        }
    }

    return maxLength;
}

int main()
{
    string str;
    cout << "Enter a string" << endl;
    getline(cin, str);

    cout << endl;

    cout << "Length of the longest word in the string is: " <<  getLongestWord(str);

    return 0;
}
