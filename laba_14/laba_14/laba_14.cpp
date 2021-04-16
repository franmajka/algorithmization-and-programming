#include <iostream>
#include <cstdlib>
#include <ctime>
#include <clocale>
#include <fstream>
#include <windows.h>

#include "LinkedList.h"

#include "Faculty.h"
#include "Speciality.h"
#include "Institute.h"
#include "InstitutesList.h"

using namespace std;


int main()
{
    srand(time(NULL));
    setlocale(LC_ALL, "rus");

    InstitutesList institutesList("data.dat");

    while (true) {
        system("cls");
        cin.clear();
        fflush(stdin);

        cout << "Главное меню:" << endl
            << "1) Вывести список университетов" << endl
            << "2) Отсортировать по проходному баллу" << endl
            << "3) Найти специальности по проходному баллу" << endl
            << "4) Найти институт по проходному баллу" << endl 
            << "5) Добавить случайный институт" << endl 
            << "6) Удалить интститут" << endl 
            << "7) Выход" << endl << endl;

        int key;
        cin >> key;

        system("cls");
        cin.clear();
        fflush(stdin);

        switch (key) {
        case 1: {
            cout << institutesList << endl;
            break;
        }
        case 2: {
            institutesList.sortByPassingScore();
            cout << "Готово" << endl;
            break;
        }
        case 3: {
            cout << "Введите промежуток на котором стоит искать специальности в формате \"от до\"" << endl;
            float from, to;
            cin >> from >> to;
            cout << endl;

            cout << institutesList.getSpecialitiesInRange(from, to);
            break;
        }
        case 4: {
            cout << "Введите средний проходной балл по институту чтобы найти подходящий" << endl;
            float passingScore;
            cin >> passingScore;

            cout << endl;

            try {
                cout << institutesList.findByPassingScore(passingScore);
            }
            catch (const char* e) {
                cout << e;
            }
            break;
        }
        case 5: {
            institutesList.append(Institute());
            cout << "Готово" << endl;
            break;
        }
        case 6: {
            cout << "Введите номер института который желаете удалить" << endl;
            int idx;
            cin >> idx;

            try {
                institutesList.pop(idx - 1);
                cout << "Готово" << endl;
            }
            catch (const char* e) {
                cout << e << endl;
            }
            break;
        }
        case 7: {
            return 0;
            break;
        }
        default: {
            cout << endl << "Попробуйте еще раз" << endl;
            break;
        }
        }

        system("pause");
    }

    return 0;
}
