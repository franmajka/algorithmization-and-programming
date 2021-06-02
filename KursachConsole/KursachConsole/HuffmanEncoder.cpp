#include "HuffmanEncoder.h"

#include <iostream>
#include <fstream>
#include <string>
#include <bitset>
#include <queue>

#include "BitsWriter.h"

#define BYTE_LENGTH 8

using namespace std;


WeightTable countSymbols(ifstream& fin)
{
	WeightTable weightTable;
	char c;

	// Читаем из файла все символы
	while (fin.read(&c, 1)) {

		// Если символ есть в хеш-таблице добавляем 1 к его 
		// частоте если нету то добавляем символ в таблицу со значением 1 
		auto it = weightTable.find(c);
		if (it != weightTable.end()) {
			it->second += 1;
		}
		else {
			weightTable.insert({ c, 1 });
		}
	}

	// Символ \0 в моей реализации отвечает за конец бинарного файла
	// Своего рода EOF но только символ
	weightTable.insert({ 0, 1 });

	return weightTable;
}

void HuffmanEncoder::writeTable(BitsWriter& bw)
{
	// Записываем в файл длину таблицы
	uint8_t tableSize = m_codesTable.size();
	bw.write(bitset<8>(tableSize).to_string());

	// Для каждой записи из таблицы записываем ascii код символа
	// количество бит которыми он кодируется и сами биты
	for (const auto& p : m_codesTable) {
		bw.write(bitset<8>(p.first).to_string());
		bw.write(bitset<8>(uint8_t(p.second.size())).to_string());
		bw.write(p.second);
	}
}

void HuffmanEncoder::writeEncodedText(BitsWriter& bw)
{
	ifstream fin(m_finname, ios::binary);
	fin.seekg(m_shift);
	char c;

	// Читаем все символы из файла и пишем в бинарный файл их коды
	while(fin.read(&c, 1)) {
		bw.write(m_codesTable[c]);
	}

	// Добавляем символ конца файла
	bw.write(m_codesTable[0]);
}

// Рекурсивно обходим дерево когда идем налево добавляем в код 0 иначе 1
void HuffmanEncoder::traversal(HuffmanEncoder::BinaryTree::Node* node, std::string code)
{
	if (!node) return;

	if (!(node->leftChild || node->rightChild)) {
		m_codesTable.insert({ node->value.first.front(), code });
	}

	if (node->leftChild) {
		traversal(node->leftChild, code + "0");
	}

	if (node->rightChild) {
		traversal(node->rightChild, code + "1");
	}
}

void HuffmanEncoder::writeToBinary(const std::string& fname)
{
	// Инициализируем вспомогательный класс для записи битов в бинарный файл
	BitsWriter bw(fname);

	ifstream fin(m_finname, ios::binary);
	char buffer;
	for (int i = 0; i < m_shift; i++) {
		fin.read(&buffer, 1);
		bw.write(bitset<8>(buffer).to_string());
	}
	fin.close();

	// Записываем таблицу
	writeTable(bw);
	// Записываем текст
	writeEncodedText(bw);

	bw.close();
}

constexpr bool std::greater<HuffmanEncoder::BinaryTree>::operator()
(const HuffmanEncoder::BinaryTree& lhs, const HuffmanEncoder::BinaryTree& rhs) const
{
	return lhs.root->value.second > rhs.root->value.second;
}

void HuffmanEncoder::encode()
{
	// Приоритетная очередь через min-heap 
	// Иными словами в начале очереди элементы с наименьшей частотой
	priority_queue<BinaryTree, vector<BinaryTree>, greater<BinaryTree>> pq;
	ifstream fin(m_finname, ios::binary);
	fin.seekg(m_shift);
	for (const auto& p : countSymbols(fin)) {
		// Для каждого символа создаем бинарное дерево которое пихаем в очередь
		pq.push(BinaryTree({ string(1, p.first), p.second }));
	}
	fin.close();

	// Сливаем все деревья в одно сливая сначала деревья корни которых имеют наименшую частоту
	// В конце символы с большей частотой будут находится ближе к корню таким образом получая более короткий код
	while (pq.size() > 1) {
		BinaryTree l(pq.top());
		pq.pop();
		BinaryTree r(pq.top());
		pq.pop();

		pq.push(BinaryTree::merge(l, r));
	}

	traversal(pq.top().root);
}

void HuffmanEncoder::printTable()
{
	for (const auto& p : m_codesTable) {
		cout << p.first << " - " << p.second << endl;
	}
}
