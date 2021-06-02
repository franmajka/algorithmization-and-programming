#include "Treap.h"

std::pair<TreapNode*, TreapNode*> split(TreapNode* node, char asymb)
{
	if (!node) return { NULL, NULL };
	// ����� ������ �� �������
	if (node->symb < asymb) {
		// ���� ���� ������ ��������� �� ���������� ����� ��� 
		if (node->rightChild) {
			auto p = split(node->rightChild, asymb);
			// ������������ ����� ��� ������ ������� ������ ���������
			node->rightChild = p.first;
			return { node, p.second };
		}

		return { node, NULL };
	}

	// ���������
	if (node->symb > asymb) {
		if (node->leftChild) {
			auto p = split(node->leftChild, asymb);
			node->leftChild = p.second;
			return { p.first, node };
		}

		return { NULL, node };
	}

	TreapNode* l = node->leftChild;
	TreapNode* r = node->rightChild;

	node->leftChild = 0;
	node->rightChild = 0;
	return { l, r };
}

TreapNode* merge(TreapNode* left, TreapNode* right)
{
	// ���� ���� �� ����������� ������ ���������� ������
	if (!left) return right;
	if (!right) return left;

	// ���� ���� ������ ������ ������ ��� ������� �� ����������
	// ������� ����� ��������� � ����� ���������� ������� ���������
	if (left->key > right->key) {
		right->leftChild = merge(left, right->leftChild);
		return right;
	}

	// ���������� ��������
	left->rightChild = merge(left->rightChild, right);
	return left;
}

TreapNode* insert(TreapNode* node, char asymb, int akey)
{
	// ���� ���� ������ ������� ����� �� ��� �����
	if (!node) return new TreapNode(asymb, akey);

	// ���� ��������� ���� ������ ��� � �������� �� ����� ����� 
	// ������� ���� ����� ���� ��� ���� ����� ������� �� �������� ������� min-heap
	if (node->key > akey) {
		// ����� ������ �� ������� � ����������� ������������ ������� ��� ����� ������
		auto p = split(node, asymb);
		TreapNode* newNode = new TreapNode(asymb, akey);
		newNode->leftChild = p.first;
		newNode->rightChild = p.second;
		return newNode;
	}

	// ����������� ����� �� ������� bst
	if (node->symb < asymb) {
		node->rightChild = insert(node->rightChild, asymb, akey);
	}
	else {
		node->leftChild = insert(node->leftChild, asymb, akey);
	}

	return node;
}

uint8_t height(TreapNode* node)
{
	if (!node) return 0;

	uint8_t leftHeight = height(node->leftChild);
	uint8_t rightHeight = height(node->rightChild);

	// �������� ������������ ������ ���� ����������� � ���������� 1 ��� ������� �������
	return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void clear(TreapNode* node)
{
	if (!node) return;

	// ����������� ������ ��� �����������
	clear(node->leftChild);
	clear(node->rightChild);

	delete node;
}
