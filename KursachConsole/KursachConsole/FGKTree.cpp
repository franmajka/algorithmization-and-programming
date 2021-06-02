#include "FGKTree.h"

#include <string>

using namespace std;

FGKTree::pSymb FGKTree::find(Node* node, char c, string code = "") const
{
	if (node->symb == c) return { node, code };

	pSymb found;
	found.first = NULL;

	if (node->leftChild) {
		found = find(node->leftChild, c, code + "0");
	}

	if (found.first) return found;

	if (node->rightChild) {
		found = find(node->rightChild, c, code + "1");
	}

	return found;
}

FGKTree::pSymb FGKTree::find(char c) const
{
	return find(m_root, c);
}

void FGKTree::clear(Node* node)
{
	if (!node) return;

	clear(node->leftChild);
	clear(node->rightChild);

	delete node;
}
