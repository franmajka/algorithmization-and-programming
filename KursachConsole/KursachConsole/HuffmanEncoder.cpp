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

	// ������ �� ����� ��� �������
	while (fin.read(&c, 1)) {

		// ���� ������ ���� � ���-������� ��������� 1 � ��� 
		// ������� ���� ���� �� ��������� ������ � ������� �� ��������� 1 
		auto it = weightTable.find(c);
		if (it != weightTable.end()) {
			it->second += 1;
		}
		else {
			weightTable.insert({ c, 1 });
		}
	}

	// ������ \0 � ���� ���������� �������� �� ����� ��������� �����
	// ������ ���� EOF �� ������ ������
	weightTable.insert({ 0, 1 });

	return weightTable;
}

void HuffmanEncoder::writeTable(BitsWriter& bw)
{
	// ���������� � ���� ����� �������
	uint8_t tableSize = m_codesTable.size();
	bw.write(bitset<8>(tableSize).to_string());

	// ��� ������ ������ �� ������� ���������� ascii ��� �������
	// ���������� ��� �������� �� ���������� � ���� ����
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

	// ������ ��� ������� �� ����� � ����� � �������� ���� �� ����
	while(fin.read(&c, 1)) {
		bw.write(m_codesTable[c]);
	}

	// ��������� ������ ����� �����
	bw.write(m_codesTable[0]);
}

// ���������� ������� ������ ����� ���� ������ ��������� � ��� 0 ����� 1
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
	// �������������� ��������������� ����� ��� ������ ����� � �������� ����
	BitsWriter bw(fname);

	ifstream fin(m_finname, ios::binary);
	char buffer;
	for (int i = 0; i < m_shift; i++) {
		fin.read(&buffer, 1);
		bw.write(bitset<8>(buffer).to_string());
	}
	fin.close();

	// ���������� �������
	writeTable(bw);
	// ���������� �����
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
	// ������������ ������� ����� min-heap 
	// ����� ������� � ������ ������� �������� � ���������� ��������
	priority_queue<BinaryTree, vector<BinaryTree>, greater<BinaryTree>> pq;
	ifstream fin(m_finname, ios::binary);
	fin.seekg(m_shift);
	for (const auto& p : countSymbols(fin)) {
		// ��� ������� ������� ������� �������� ������ ������� ������ � �������
		pq.push(BinaryTree({ string(1, p.first), p.second }));
	}
	fin.close();

	// ������� ��� ������� � ���� ������ ������� ������� ����� ������� ����� ��������� �������
	// � ����� ������� � ������� �������� ����� ��������� ����� � ����� ����� ������� ������� ����� �������� ���
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
