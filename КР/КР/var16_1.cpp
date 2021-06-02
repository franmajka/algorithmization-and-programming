// ���� ����� ��-02
// https://www.onlinegdb.com/online_c++_compiler

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// ������� ������ � �������
void printVec(const vector<int>& vec) {
    // � ranged for ������� reference ����� �� ����������
    // �������� � ����� ������� ������� ���������� ���������
    for (const int& el : vec) {
        cout << el << " ";
    }
    cout << endl;
}

// ��������� ������ �������� ��������������� length ����������
void initVec(vector<int>& vec, int length) {
    // ������� ���� ������ �� ������ ���� ��� ���-�� ����
    // ����� �� ����� �������� ��������� length ���������
    vec.clear();

    for (int i = 0; i < length; i++) {
        // ���������� �������� �� ���������� 0-9
        vec.push_back(rand() % 10);
    }
}

// ������� ������ �������� ���� �� ���� ������
// ������� � ��������
// 1 1 1 2 -> 1 2
void removeCopySeries(vector<int>& vec) {
    if (!vec.size()) return;

    // ��������� ���������� �����
    int lastNumber = vec.front();
    for (auto it = vec.begin() + 1; it != vec.end();) {
        // ������� ��������� � ����������
        if (*it == lastNumber) {
            // �������
            it = vec.erase(it, it + 1);
            continue;
        }

        // �������� ���������� ����� �����
        lastNumber = *it;
        ++it;
    }
}

int main()
{
    srand(time(NULL));

    int length;
    cout << "Enter a length of array" << endl;
    cin >> length;

    vector<int> vec;
    initVec(vec, length);

    cout << endl;

    cout << "Random generated array" << endl;
    printVec(vec);

    removeCopySeries(vec);

    cout << endl;

    cout << "Your result" << endl;
    printVec(vec);

    return 0;
}
