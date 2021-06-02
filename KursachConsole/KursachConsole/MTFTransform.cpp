#include "MTFTransform.h"

#include <fstream>
#include <set>
#include <list>
#include <vector>
#include <unordered_map>

#include "Treap.h"

using namespace std;

pair<TreapNode*, uint8_t> findInTreap(TreapNode* node, char symb, int key, uint8_t code)
{
	// Если правильно испольовать алгоритм такого произойти не должно но на всякий случай...
	if (!node) throw "Unexpected behavior in findInTreap";

	// Если нашли нужный узел вовращаем его вместе с кодом
	if (node->symb == symb) return { node, code };

	TreapNode* nextNode = 0;
	uint8_t lesser = 0;

	// Осуществляем рекурсивный поиск по дереву используя особенность bst
	// При переходе на одного из детей узла считаем количество узлов с меньшим ключом чем в другом поддереве
	if (node->symb < symb) {
		nextNode = node->rightChild;
		if (node->leftChild && node->leftChild->key < key) lesser = getLesserThan(node->leftChild, key);
	}
	else {
		nextNode = node->leftChild;
		if (node->rightChild && node->rightChild->key < key) lesser = getLesserThan(node->rightChild, key);
	}

	// Сам рекурсивный вызов
	return findInTreap(nextNode, symb, key, code + lesser + 1);
}

uint8_t getLesserThan(TreapNode* node, int key)
{
	if (!node) return 0;

	// Предполагаем что если функция вызвана то этот узел уже автоматически включается
	uint8_t found = 1;

	// Пользуемся особенностью кучи рекурсивно считаем количество узлов меньше чем key 
	if (node->leftChild && node->leftChild->key < key) found += getLesserThan(node->leftChild, key);
	if (node->rightChild && node->rightChild->key < key) found += getLesserThan(node->rightChild, key);

	return found;
}

int mtf(string finname, string foutname, int shift)
{
	ifstream fin(finname, ios::binary);
	ofstream fout(foutname, ios::binary);

	// Копируем все данные которые не должны модифицироваться алгоритмом
	char buffer;
	for (int i = 0; i < shift; i++) {
		fin.read(&buffer, 1);
		fout.write(&buffer, 1);
	}
	
	set<char> alphabet;
	char c;

	// Построение алфавита (уникальные символы из которых состоит текст)
	while (fin.get(c)) {
		alphabet.insert(c);
	}

	// Создаем таблицу символов и их приоритетов для правильного подсчета кода
	unordered_map<char, int> keys;
	TreapNode* treap = 0;
	int counter = 0;

	// Построение treap на основе алфавита
	for (char symb : alphabet) {
		treap = insert(treap, symb, counter);
		keys.insert({ symb, counter });
		fout.write(&symb, 1);
		counter++;
	}

	// В качестве разделителя между алфавитом и закодированным текстом используем символ \0
	char delim = 0;
	fout.write(&delim, 1);
	fin.clear();
	fin.seekg(shift);

	// Для того чтобы нужный узел находился в корне treap его приоритет должен
	// быть меньше чем у всех узлов в дереве это реализуется через minKey
	int minKey = 0;
	while (fin.get(c)) {
		// Ищем в дереве символ
		auto found = findInTreap(treap, c, keys[c]);
		// Увеличиваем на 1 чтобы \0 был зарезервирован
		char code = found.second + 1;
		// Его код записываем в выходной файл
		fout.write(&code, 1);

		// Модифицируем дерево чтобы символ всплыл наверх
		auto splitted = split(treap, c);
		found.first->key = --minKey;
		keys[c] = minKey;
		treap = merge(merge(splitted.first, found.first), splitted.second);
	}

	fin.close();
	fout.close();
	clear(treap);

	return alphabet.size() + 1;
}

int mtfSlower(std::string finname, std::string foutname, int shift)
{
	ifstream fin(finname, ios::binary);
	ofstream fout(foutname, ios::binary);
	set<char> alphabet;
	char c;

	// Копируем все данные которые не должны модифицироваться алгоритмом
	char buffer;
	for (int i = 0; i < shift; i++) {
		fin.read(&buffer, 1);
		fout.write(&buffer, 1);
	}

	// Построение алфавита (уникальные символы из которых состоит текст)
	while (fin.get(c)) {
		alphabet.insert(c);
	}

	list<char> seq;
	for (char symb : alphabet) {
		seq.push_back(symb);
		fout.write(&symb, 1);
	}

	// В качестве разделителя между алфавитом и закодированным текстом используем символ \0
	char delim = '\0';
	fout.write(&delim, 1);
	fin.clear();
	fin.seekg(shift);

	while (fin.get(c)) {
		// Начинаем 1 чтобы \0 был зарезервирован
		int counter = 1;
		for (auto it = seq.begin(); it != seq.end(); ++it, ++counter) {
			if (*it != c) continue;

			// Записываем в выходной файл код
			fout.write((char*)&counter, 1);
			seq.erase(it);
			seq.push_front(c);

			break;
		}
	}

	fin.close();
	fout.close();
	return alphabet.size() + 1;
}

void mtfDecode(std::string finname, std::string foutname, int shift)
{
	ifstream fin(finname, ios::binary);
	ofstream fout(foutname, ios::binary);
	vector<char> seq;

	// Копируем все данные которые не должны декодироваться алгоритмом
	char buffer;
	for (int i = 0; i < shift; i++) {
		fin.read(&buffer, 1);
		fout.write(&buffer, 1);
	}

	char c;
	int counter = 0;

	// Считываем алфавит
	while (fin) {
		fin.read(&c, 1);
		if (!c) break;

		seq.push_back(c);
		counter++;
	}
	
	int minKey = 0;
	fin.read(&c, 1);
	while (fin) {
		// Символ который мы считываем выступает как индекс + 1 
		// то есть чтобы его раскодировать нужно посмотреть в текущую последовательность
		char code = seq[c - 1];
		fout.write(&code, 1);

		// Модифицируем последовательность чтобы последний встреченный символ был в начале
		for (int i = c - 1; i > 0; i--) {
			swap(seq[i], seq[i - 1]);
		}

		seq[0] = code;
		fin.read(&c, 1);
	}

	fin.close();
	fout.close();
}
