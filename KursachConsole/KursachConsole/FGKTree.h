#pragma once

#include <string>

struct FGKTree
{
	struct Node {
		Node(char c) : quantity(1), symb(c), parent(0), leftChild(0), rightChild(0) {}
		Node() : Node(0) {}

		unsigned quantity;
		char symb;

		Node* parent;
		Node* leftChild;
		Node* rightChild;

		Node* sibling() { return parent ? (parent->leftChild == this ? parent->rightChild : parent->leftChild) : 0; }
	};

	using pSymb = std::pair<Node*, std::string>;

	FGKTree() { m_root = new Node(); }
	~FGKTree() { clear(); }

	pSymb find(Node* node, char c, std::string code) const;
	pSymb find(char c) const;

	void update(Node* node);
	void insert(char c);

	void clear(Node* node);
	void clear() { clear(m_root); }

	Node* m_root;
};

