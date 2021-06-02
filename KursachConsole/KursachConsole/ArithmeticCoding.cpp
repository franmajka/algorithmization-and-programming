#include "ArithmeticCoding.h"

#include <list>
#include <map>

#include "BitsWriter.h"
#include "BitsReader.h"

#include <iostream>
#include "Timer.h"

#define PROBABILITY_LENGTH 3
#define BYTE_LENGTH 8

// В классическом алгоритме используется 1 но
// LongDecimal хранит лишь дробную часть так что
// ради наиболее короткой двоичной записи 1 заменена на .5
#define ONE .5

using namespace std;

list<Range> Range::split(const map<unsigned char, LongDecimal>& probabilities) const
{
    list<Range> ranges;

    LongDecimal distance = m_high - m_low;
    LongDecimal currLow = m_low;

    for (const auto& probability : probabilities) {
        LongDecimal currDistance = distance * probability.second;
        ranges.push_back(Range(currLow, currLow + currDistance, probability.first));
        currLow += currDistance;
    }

    return ranges;
}

std::map<unsigned char, LongDecimal> getProbabilities(std::ifstream& fin)
{
    map<unsigned char, double> probabilities;
    size_t counter = 1; // Включаем \0
    size_t startPos = fin.tellg();
    char c;

    while (fin.get(c)) {
        auto it = probabilities.find(c);
        if (it != probabilities.end()) {
            it->second++;
        }
        else {
            probabilities.insert({ c, 1 });
        }

        counter++;
    }

    probabilities.insert({ 0, 1 });

    for (auto& p : probabilities) {
        p.second = p.second / counter;
    }

    fin.clear();
    fin.seekg(startPos);

    map<unsigned char, LongDecimal> res;
    for (const auto& p : probabilities) {
        res.insert({ p.first, LongDecimal(p.second, PROBABILITY_LENGTH) });
    }

    return res;
}

unsigned arithmeticEncode(std::string finname, std::string foutname, unsigned shift)
{
    ifstream fin(finname, ios::binary);
    ofstream fout(foutname, ios::binary);

    // Переписываем зарезервированную информацию
    char buffer;
    for (unsigned i = 0; i < shift; i++) {
        fin.read(&buffer, 1);
        fout.write(&buffer, 1);
    }

    Timer t;

    // Считаем вероятности каждого символа с учетом символа конца \0
    map<unsigned char, LongDecimal> probabilities = getProbabilities(fin);

    cout << "Getting probabilities - " << t.elapsed() << "s" << endl;

    unsigned alphabetLength = 0;
    char zero = '\0';

    t.reset();
    // Записываем алфавит с вероятностями в файл сохраняя количество байт выделеных на него
    for (auto& p : probabilities) {
        fout.write((char*)&p.first, 1);

        uint8_t counter = 0;
        for (auto& byte : p.second.getBytes()) {
            fout.write((char*)&byte, 1);
            counter++;
        }

        for (; counter < PROBABILITY_LENGTH; counter++) {
            fout.write(&zero, 1);
        }

        alphabetLength += 1 + PROBABILITY_LENGTH;
    }

    // Указаываем конец алфавита
    fout.write(&zero, 1);
    alphabetLength++;
    cout << "Writing alphabet - " << t.elapsed() << "s" << endl;

    t.reset();
    // Разбиваем отрезок [0; 1) на части в соответствии с вероятностями символов
    list<Range> ranges = Range(0, ONE, 0).split(probabilities);
    char c;

    // Читаем текст и продолжаем дробить отрезки которым отвечает текущий 
    // символ на меньшие в соответствии с вероятностями всех символов алфавита
    while (fin.get(c)) {
        for (const Range& range : ranges) {
            if (range.includes(c)) {
                ranges = range.split(probabilities);
                break;
            }
        }
    }
    cout << "Splitting range - " << t.elapsed() << "s" << endl;

    t.reset();
    // Находим символ конца строки в результующих отрезках и записываем число что принадлежит этому отрезку
    // Зачастую записывается нижняя граница или число что слегка больше
    for (const Range& range : ranges) {
        if (!range.includes('\0')) continue;

        LongDecimal low = range.getLow();
        LongDecimal high = range.getHigh();
        
        // Находим все совпадающие биты
        LongDecimal bitwiseAnd = low & high;
        // Находим все не совпадающие
        LongDecimal bitwiseXor = low ^ high;

        // Находим количество бит до первого не совпадающего
        unsigned counter = 0;
        while ((bitwiseXor & .5) == 0) {
            bitwiseXor <<= 1;
            counter++;
        }

        unsigned shift = 1;
        low <<= (counter + 1);
        while ((low & .5) == .5) {
            low <<= 1;
            shift++;
        }

        // Для того чтобы получить самое короткое представление числа
        // мы берем все первые совпадающие биты и дописываем shift нулевых бит и 1 
        // так как первый несовпадающий бит для левой границы будет 0 а для правой 1

        LongDecimal mask = 0;
        for (unsigned i = 0; i < (counter + shift); i++) {
            mask >>= 1;
            mask |= .5;
        }

        // Просто обрезает лишние биты
        low = range.getLow() & mask;

        // Добавляет несколько бит чтобы число было точно меньше верхней границы
        // но при этом больше нижней и было как можно более коротким
        mask = .5;
        mask >>= shift + counter;

        low |= mask;

        for (auto& byte : low.getBytes()) {
            fout.write((char*)&byte, 1);
        }
    }
    cout << "Writing coded - " << t.elapsed() << "s" << endl;
    

    fin.close();
    fout.close();

    return alphabetLength;
}

void arithmeticDecode(string finname, string foutname, unsigned shift) {
    ifstream fin(finname, ios::binary);
    ofstream fout(foutname, ios::binary);

    char buffer;
    for (int i = 0; i < shift; i++) {
        fin.read(&buffer, 1);
        fout.write(&buffer, 1);
    }

    map<unsigned char, LongDecimal> probabilities;

    char c;
    // Читаем \0 так как он всегда есть в начале алфавита
    // чтобы когда мы еще раз прочитаем \0 это значило конец алфавита
    fin.read(&c, 1); 

    unsigned char* probabilityBuffer = new unsigned char[PROBABILITY_LENGTH];
    do {
        fin.read((char*)probabilityBuffer, PROBABILITY_LENGTH);
        probabilities.insert({ c, LongDecimal(probabilityBuffer, PROBABILITY_LENGTH) });
        fin.read(&c, 1);
    } while (c);

    delete[] probabilityBuffer;

    vector<unsigned char> bytes;
    while (fin.get(c)) {
        bytes.push_back(c);
    }
    LongDecimal coded(bytes);

    list<Range> ranges = Range(0, ONE, 0).split(probabilities);

    while (true) {
        for (const Range& range : ranges) {
            if (!range.includes(coded)) continue;

            char c = range.getC();

            // Если встречаем символ конца строки то раскодирование закончено
            if (c == 0) {
                fin.close();
                fout.close();
                return;
            }

            fout.write(&c, 1);

            ranges = range.split(probabilities);
            break;
        }
    }
}