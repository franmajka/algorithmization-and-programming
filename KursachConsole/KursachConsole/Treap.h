#pragma once

#include <utility>
#include <cstdint>

// ���� ����������� ������
struct TreapNode {
	char symb;
	int key;

	TreapNode* leftChild;
	TreapNode* rightChild;

	TreapNode(char asymb, int akey) : symb(asymb), key(akey), leftChild(0), rightChild(0) {}
};

// ��������� ���� ������ �� ��� ��������� �� �����
std::pair<TreapNode*, TreapNode*> split(TreapNode* node, char asymb);
// ������� ��� ��������� � ����
TreapNode* merge(TreapNode* left, TreapNode* right);

// ��������� ����� ����
TreapNode* insert(TreapNode* node, char asymb, int akey);

// ���������� ������� �������� ������
uint8_t height(TreapNode* node);
// ������� ���������� ������
void clear(TreapNode* node);

