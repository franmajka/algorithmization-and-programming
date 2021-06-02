// Рудік Андрій ДА-02
// https://www.onlinegdb.com/online_c++_compiler

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

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
        // Закидываем элементы на промежутке 0-9
        vec.push_back(rand() % 10);
    }
}

// Удаляет лишние элементы если те идут подряд
// Вариант с вектором
// 1 1 1 2 -> 1 2
void removeCopySeries(vector<int>& vec) {
    if (!vec.size()) return;

    // Сохраняем предыдущее число
    int lastNumber = vec.front();
    for (auto it = vec.begin() + 1; it != vec.end();) {
        // Текущее совпадает с предыдущим
        if (*it == lastNumber) {
            // Удаляем
            it = vec.erase(it, it + 1);
            continue;
        }

        // Заменяем предыдущее число новым
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
