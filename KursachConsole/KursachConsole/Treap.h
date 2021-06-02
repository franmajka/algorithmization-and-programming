#pragma once

#include <utility>
#include <cstdint>

// Узел декартового дерева
struct TreapNode {
	char symb;
	int key;

	TreapNode* leftChild;
	TreapNode* rightChild;

	TreapNode(char asymb, int akey) : symb(asymb), key(akey), leftChild(0), rightChild(0) {}
};

// Разделяет одно дерево на два поддерева по ключу
std::pair<TreapNode*, TreapNode*> split(TreapNode* node, char asymb);
// Сливает два поддерева в одно
TreapNode* merge(TreapNode* left, TreapNode* right);

// Добавляет новый узел
TreapNode* insert(TreapNode* node, char asymb, int akey);

// Рекурсивно считает высосоту дерева
uint8_t height(TreapNode* node);
// Очищает выделенную память
void clear(TreapNode* node);

