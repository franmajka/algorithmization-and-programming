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
	// ���� ��������� ����������� �������� ������ ��������� �� ������ �� �� ������ ������...
	if (!node) throw "Unexpected behavior in findInTreap";

	// ���� ����� ������ ���� ��������� ��� ������ � �����
	if (node->symb == symb) return { node, code };

	TreapNode* nextNode = 0;
	uint8_t lesser = 0;

	// ������������ ����������� ����� �� ������ ��������� ����������� bst
	// ��� �������� �� ������ �� ����� ���� ������� ���������� ����� � ������� ������ ��� � ������ ���������
	if (node->symb < symb) {
		nextNode = node->rightChild;
		if (node->leftChild && node->leftChild->key < key) lesser = getLesserThan(node->leftChild, key);
	}
	else {
		nextNode = node->leftChild;
		if (node->rightChild && node->rightChild->key < key) lesser = getLesserThan(node->rightChild, key);
	}

	// ��� ����������� �����
	return findInTreap(nextNode, symb, key, code + lesser + 1);
}

uint8_t getLesserThan(TreapNode* node, int key)
{
	if (!node) return 0;

	// ������������ ��� ���� ������� ������� �� ���� ���� ��� ������������� ����������
	uint8_t found = 1;

	// ���������� ������������ ���� ���������� ������� ���������� ����� ������ ��� key 
	if (node->leftChild && node->leftChild->key < key) found += getLesserThan(node->leftChild, key);
	if (node->rightChild && node->rightChild->key < key) found += getLesserThan(node->rightChild, key);

	return found;
}

int mtf(string finname, string foutname, int shift)
{
	ifstream fin(finname, ios::binary);
	ofstream fout(foutname, ios::binary);

	// �������� ��� ������ ������� �� ������ ���������������� ����������
	char buffer;
	for (int i = 0; i < shift; i++) {
		fin.read(&buffer, 1);
		fout.write(&buffer, 1);
	}
	
	set<char> alphabet;
	char c;

	// ���������� �������� (���������� ������� �� ������� ������� �����)
	while (fin.get(c)) {
		alphabet.insert(c);
	}

	// ������� ������� �������� � �� ����������� ��� ����������� �������� ����
	unordered_map<char, int> keys;
	TreapNode* treap = 0;
	int counter = 0;

	// ���������� treap �� ������ ��������
	for (char symb : alphabet) {
		treap = insert(treap, symb, counter);
		keys.insert({ symb, counter });
		fout.write(&symb, 1);
		counter++;
	}

	// � �������� ����������� ����� ��������� � �������������� ������� ���������� ������ \0
	char delim = 0;
	fout.write(&delim, 1);
	fin.clear();
	fin.seekg(shift);

	// ��� ���� ����� ������ ���� ��������� � ����� treap ��� ��������� ������
	// ���� ������ ��� � ���� ����� � ������ ��� ����������� ����� minKey
	int minKey = 0;
	while (fin.get(c)) {
		// ���� � ������ ������
		auto found = findInTreap(treap, c, keys[c]);
		// ����������� �� 1 ����� \0 ��� ��������������
		char code = found.second + 1;
		// ��� ��� ���������� � �������� ����
		fout.write(&code, 1);

		// ������������ ������ ����� ������ ������ ������
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

	// �������� ��� ������ ������� �� ������ ���������������� ����������
	char buffer;
	for (int i = 0; i < shift; i++) {
		fin.read(&buffer, 1);
		fout.write(&buffer, 1);
	}

	// ���������� �������� (���������� ������� �� ������� ������� �����)
	while (fin.get(c)) {
		alphabet.insert(c);
	}

	list<char> seq;
	for (char symb : alphabet) {
		seq.push_back(symb);
		fout.write(&symb, 1);
	}

	// � �������� ����������� ����� ��������� � �������������� ������� ���������� ������ \0
	char delim = '\0';
	fout.write(&delim, 1);
	fin.clear();
	fin.seekg(shift);

	while (fin.get(c)) {
		// �������� 1 ����� \0 ��� ��������������
		int counter = 1;
		for (auto it = seq.begin(); it != seq.end(); ++it, ++counter) {
			if (*it != c) continue;

			// ���������� � �������� ���� ���
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

	// �������� ��� ������ ������� �� ������ �������������� ����������
	char buffer;
	for (int i = 0; i < shift; i++) {
		fin.read(&buffer, 1);
		fout.write(&buffer, 1);
	}

	char c;
	int counter = 0;

	// ��������� �������
	while (fin) {
		fin.read(&c, 1);
		if (!c) break;

		seq.push_back(c);
		counter++;
	}
	
	int minKey = 0;
	fin.read(&c, 1);
	while (fin) {
		// ������ ������� �� ��������� ��������� ��� ������ + 1 
		// �� ���� ����� ��� ������������� ����� ���������� � ������� ������������������
		char code = seq[c - 1];
		fout.write(&code, 1);

		// ������������ ������������������ ����� ��������� ����������� ������ ��� � ������
		for (int i = c - 1; i > 0; i--) {
			swap(seq[i], seq[i - 1]);
		}

		seq[0] = code;
		fin.read(&c, 1);
	}

	fin.close();
	fout.close();
}
