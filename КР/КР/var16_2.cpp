// Рудік Андрій ДА-02
// https://www.onlinegdb.com/online_c++_compiler

#include <iostream>
#include <string>

using namespace std;

// Считает максимальную длину слова в строке
int getLongestWord(const string& str) {
    // По умолчанию слово еще не началось
    // Нормальные люди пишут "auto wordBegin" но не в этот раз
    string::const_iterator wordBegin = str.end();
    int maxLength = -1;

    // Проходимся по всем символам строки
    for (string::const_iterator it = str.begin();; ++it) {
        // Если мы дошли до конца слова
        if ((*it == ' ' || it == str.end()) && wordBegin != str.end()) {
            // Посчитали его длину как длину между итераторами
            // Можно было сделать как обычный счетчик
            int wordLength = distance(wordBegin, it);

            // Если длина текущего слова больше максимально заменяем макс
            if (wordLength > maxLength) maxLength = wordLength;

            // Так как конец строки может быть также концом слова
            // мы не прекращаем выполнение программы как конец for
            // а просто делаем break
            if (it == str.end()) break;

            // Обнуляем начало слова
            wordBegin = str.end();

            continue;
        }

        if (it == str.end()) break;

        // Ставим начало слова
        // По хорошему тут нужно делать проверку на все
        // пробельные символы с помощью какого-то regex
        // но я не хотел усложняь код так что все
        // \n \r \0 считаются символом строки
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
