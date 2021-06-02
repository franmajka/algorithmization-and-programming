#include "Treap.h"

std::pair<TreapNode*, TreapNode*> split(TreapNode* node, char asymb)
{
	if (!node) return { NULL, NULL };
	// Делим дерево по символу
	if (node->symb < asymb) {
		// Если есть правое поддерево то рекурсивно делим его 
		if (node->rightChild) {
			auto p = split(node->rightChild, asymb);
			// Присоеденяем часть что меньше символа левому поддереву
			node->rightChild = p.first;
			return { node, p.second };
		}

		return { node, NULL };
	}

	// Зеркально
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
	// Если одно из поддеревьев пустое возвращаем другое
	if (!left) return right;
	if (!right) return left;

	// Если ключ левого дерева больше чем правого то рекурсивно
	// сливаем левое поддерево с левым поддеревом правого поддерева
	if (left->key > right->key) {
		right->leftChild = merge(left, right->leftChild);
		return right;
	}

	// Зеркальная операция
	left->rightChild = merge(left->rightChild, right);
	return left;
}

TreapNode* insert(TreapNode* node, char asymb, int akey)
{
	// Если узел пустой создаем новый на его место
	if (!node) return new TreapNode(asymb, akey);

	// Если приоритет узла больше чем у будущего то самое время 
	// создать этот новый узел для того чтобы случаем не нарушить условие min-heap
	if (node->key > akey) {
		// Делим дерево по символу и присваиваем получившиеся дерявья как детей новому
		auto p = split(node, asymb);
		TreapNode* newNode = new TreapNode(asymb, akey);
		newNode->leftChild = p.first;
		newNode->rightChild = p.second;
		return newNode;
	}

	// Рекурсивный обход по канонам bst
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

	// Выбираем максимальную высоту двух поддеревьев и прибавляем 1 как текущий элемент
	return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

void clear(TreapNode* node)
{
	if (!node) return;

	// Рекурсивные вызовы для поддеревьев
	clear(node->leftChild);
	clear(node->rightChild);

	delete node;
}
