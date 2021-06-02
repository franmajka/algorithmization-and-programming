// ���� ����� ��-02
// https://www.onlinegdb.com/online_c++_compiler

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// ������� ����� ��������� � �������� ���������� �������
// ��� � ��� ������� � ����� ��������� ������ ��� reference
int getOddSumIterative(const vector<int>& vec) {
    int sum = 0;

    for (int i = 0; i < vec.size(); i++) {
        // �� ������� ���������� � ����
        // �������� �������� ����� �������� ������ ��������
        if (i % 2 == 0) sum += vec[i];
    }

    return sum;
}

// ���������� ������� ����� �������� ��������� �������
int getOddSumRecursive(const vector<int>& vec, int pos, int sum) {
    // ���� �� �������� ����� ������� ���������� �����
    if (pos == vec.size()) return sum;

    // ���� ������� �������� ���������� ��������
    // ������� � ����������� ������ �� ������� �������
    // ����� ����������� ������� �������
    // � �������� ��������� ��������� ��������� ���������
    return pos % 2 == 0 ?
        getOddSumRecursive(vec, pos + 1, sum + vec[pos]) :
        getOddSumRecursive(vec, pos + 1, sum);
}

// ������� ������ ��������� ����������� �������
// ��� ��� �� ��������� ��� ��� ���������
int getOddSumRecursive(const vector<int>& vec) {
    getOddSumRecursive(vec, 0, 0);
}

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
        // ���������� �������� �� ���������� 0-99
        vec.push_back(rand() % 100);
    }
}

int main()
{
    srand(time(NULL));

    int length;
    cout << "Enter a length of array" << endl;
    cin >> length;

    cout << endl;

    vector<int> vec;
    initVec(vec, length);

    cout << "Random generated array" << endl;
    printVec(vec);

    cout << endl;

    cout << "Sum of odd numbers in array:" << endl;
    cout << "Iterative: " << getOddSumIterative(vec) << endl;
    cout << "Recursive: " << getOddSumRecursive(vec) << endl;

    return 0;
}
