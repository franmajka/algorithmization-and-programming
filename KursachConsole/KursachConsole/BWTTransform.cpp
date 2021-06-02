#include "BWTTransform.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

#include "Timer.h"

using namespace std;

int bwt(std::string finname, std::string foutname, int shift)
{
	ifstream fin(finname, ios::binary);
	ofstream fout(foutname, ios::binary);

	char buffer;
	for (int i = 0; i < shift; i++) {
		fin.read(&buffer, 1);
		fout.write(&buffer, 1);
	}

	// Читает изначальные данные
	char c;
	string initial = "";
	while (fin.get(c)) {
		initial.push_back(c);
	}

	const char* pch = initial.c_str();

	fin.close();

	Timer t;
	// Создает массив циклических сдвигов
	// Пример initial == "ABC"
	// { "ABC", "BCA", "CAB" }
	vector<CyclicString> cyclicShifts;
	for (unsigned i = 0; i < initial.size(); i++) {
		cyclicShifts.push_back(CyclicString(pch, i));
	}

	cout << "CyclicShifts - " << t.elapsed() << endl;

	t.reset();
	// Отсортировывает массив циклических сдвигов в алфавитном порядке
	sort(cyclicShifts.begin(), cyclicShifts.end());
	cout << "Sort - " << t.elapsed() << endl;

	// Записывает в файл индекс изначальной строки в отсортированном массиве 
	// Необходимо для декодирования
	for (unsigned i = 0; i < cyclicShifts.size(); i++) {
		if (cyclicShifts[i].getShift() == 0) {
			fout.write((char*)&i, sizeof(i));
			break;
		}
	}

	t.reset();
	// Записывает последние буквы всех строк отсортированного массива
	if (initial.size()) {
		for (const CyclicString& str : cyclicShifts) {
			char last = str.getLastSymb();
			fout.write(&last, 1);
		}
	}
	cout << "LastLetters - " << t.elapsed() << endl;
	
	fout.close();

	return sizeof(unsigned);
}

void bwtDecode(std::string finname, std::string foutname, int shift)
{
	ifstream fin(finname, ios::binary);
	ofstream fout(foutname, ios::binary);

	char buffer;
	for (int i = 0; i < shift; i++) {
		fin.read(&buffer, 1);
		fout.write(&buffer, 1);
	}

	// Считывает позицию раскодированой строки
	unsigned initialPos;
	fin.read((char*)&initialPos, sizeof(initialPos));

	// Читает закодированую строку
	char c;
	string coded;
	while (fin.get(c)) {
		coded.push_back(c);
	}

	fin.close();

	map<char, unsigned> count;
	for (char c : coded) {
		auto it = count.find(c);
		if (it == count.end()) {
			count.insert({ c, 1 });
		}
		else {
			it->second++;
		}
	}

	unsigned sum = 0;
	for (auto it = count.begin(); it != count.end(); ++it) {
		unsigned freq = it->second;
		it->second = sum;
		sum += freq;
	}

	vector<unsigned> table(coded.size(), 0);
	for (unsigned i = 0; i < coded.size(); i++) {
		table[count.find(coded[i])->second++] = i;
	}

	// Достаем раскодированую строку по индексу
	unsigned currIdx = initialPos;
	unsigned counter = 0;
	while (counter < coded.size()) {
		currIdx = table[currIdx];
		fout.write(&coded[currIdx], 1);
		counter++;
	}

	fout.close();
}

bool CyclicString::operator<(const CyclicString& other) const
{
	const char* lstart = m_pch + m_shift;
	const char* lpch = lstart;
	const char* rpch = other.m_pch + other.m_shift;
	int counter = 0;

	while (*lpch == *rpch) {
		if (*(++lpch) == 0) lpch = m_pch;
		if (*(++rpch) == 0) rpch = other.m_pch;
		if (lpch == lstart) break;
	}

	return *lpch < *rpch;
}
