#include "RLE.h"

#include <fstream>

#define INT8_MAX 127
// Потому что если мы инвертируем знак -128 мы не получим +128
#define INT8_MIN -127

using namespace std;

void rle(std::string finname, std::string foutname, unsigned shift)
{
    ifstream fin(finname, ios::binary);
    ofstream fout(foutname, ios::binary);

    char buffer;
    for (unsigned i = 0; i < shift; i++) {
        fin.read(&buffer, 1);
        fout.write(&buffer, 1);
    }

    char c;
    char last;

    fin.get(last);
    int8_t counter = 0;
    string unrepeatable(1, last);

    while (fin.get(c)) {
        if (c == last) {
            if (counter < 0) {
                fout.write((char*)&counter, 1);
                auto str = unrepeatable.c_str();
                fout.write(str, -counter);

                counter = 0;
            }
            unrepeatable = "";
            counter++;
        }
        else {
            if (counter > 0) {
                counter++;
                fout.write((char*)&counter, 1);
                fout.write(&last, 1);
                counter = 0;
            }
            else {
                counter--;
            }

            unrepeatable += c;
        }

        if (counter == INT8_MAX) {
            fout.write((char*)&counter, 1);
            fout.write(&last, 1);
            counter = 0;
        }
        else if (counter == INT8_MIN) {
            auto str = unrepeatable.c_str();
            fout.write((char*)&counter, 1);
            fout.write(str, -counter);
            counter = 0;
            unrepeatable = unrepeatable.back();
        }
        last = c;
    }
    
    counter += counter > 0 ? 1 : -1;
    fout.write((char*)&counter, 1);
    if (counter > 0) {
        fout.write(&c, 1);
    }
    else {
        auto str = unrepeatable.c_str();
        fout.write(str, -counter);
    }

    fin.close();
    fout.close();
}

void rleDecode(std::string finname, std::string foutname, unsigned shift)
{
    ifstream fin(finname, ios::binary);
    ofstream fout(foutname, ios::binary);

    char buffer;
    for (int i = 0; i < shift; i++) {
        fin.read(&buffer, 1);
        fout.write(&buffer, 1);
    }

    char n;
    char c;
    while (fin.get(n)) {
        if (n > 0) {
            fin.get(c);
            for (int8_t i = 0; i < n; i++) {
                fout.write(&c, 1);
            }
            continue;
        }
        
        n = -n;
        for (int8_t i = 0; i < n; i++) {
            fin.get(c);
            fout.write(&c, 1);
        }
    }

    fin.close();
    fout.close();
}
