// Рудік Андрій ДА-02
// https://www.onlinegdb.com/online_c++_compiler

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Считает сумму элементов с непарным порядковым номером
// Как и все функции в файле принимают вектор как reference
int getOddSumIterative(const vector<int>& vec) {
    int sum = 0;

    for (int i = 0; i < vec.size(); i++) {
        // Тк индексы начинаются с нуля
        // непарные элементы будут отвечать парным индексам
        if (i % 2 == 0) sum += vec[i];
    }

    return sum;
}

// Рекурсивно считает сумму непарных элементов массива
int getOddSumRecursive(const vector<int>& vec, int pos, int sum) {
    // Если мы достигли конца вектора возвращаем сумму
    if (pos == vec.size()) return sum;

    // Если элемент непарный рекурсивно вызываем
    // функцию с увеличенной суммой на текущий элемент
    // Иначе увеличиваем тоолько позицию
    // В качестве условного оператора использую тернарный
    return pos % 2 == 0 ?
        getOddSumRecursive(vec, pos + 1, sum + vec[pos]) :
        getOddSumRecursive(vec, pos + 1, sum);
}

// Обертка вокруг настоящей рекурсивной функции
// так как та принимает еще доп параметры
int getOddSumRecursive(const vector<int>& vec) {
    getOddSumRecursive(vec, 0, 0);
}

// Выводит вектор в консоль
void printVec(const vector<int>& vec) {
    // В ranged for получаю reference чтобы не копировать
    // элементы и таким образом ускоряю выполнение программы
    for (const int& el : vec) {
        cout << el << " ";
    }
    cout << endl;
}

// Заполняет вектор случайно сгенерироваными length элементами
void initVec(vector<int>& vec, int length) {
    // Очищает весь вектор на случай если там что-то было
    // чтобы по итогу осталось конкретно length элементов
    vec.clear();

    for (int i = 0; i < length; i++) {
        // Закидываем элементы на промежутке 0-99
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
