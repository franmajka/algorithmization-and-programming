#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "BitsWriter.h"

using WeightTable = std::unordered_map<char, unsigned>;

// ������� ������� ������������ ������� ������� �������� � ������
WeightTable countSymbols(std::ifstream& fin);

class HuffmanEncoder
{
public:
	// ���������� ������� �������� ���
	using WeightString = std::pair<std::string, unsigned>;
	using CodesTable = std::unordered_map<char, std::string>;

	// ���������������� ��������� ��������� ������
	struct BinaryTree
	{
		// ���� ��������� ������
		// ������ ����� ������� � ���� ������ � ��� ������� � ������
		struct Node {
			WeightString value;

			Node* leftChild = NULL;
			Node* rightChild = NULL;

			Node() : leftChild(NULL), rightChild(NULL) {}
			Node(const WeightString& avalue) : Node() {
				value = avalue;
			}

			// ����������� �����������
			Node(const Node& anode) {
				value = anode.value;

				leftChild = anode.leftChild ? new Node(*anode.leftChild) : NULL;
				rightChild = anode.rightChild ? new Node(*anode.rightChild) : NULL;
			}
		};

		// ������ ������
		Node* root;

		// ��������� ����������� � ����������
		BinaryTree() : root(NULL) {};
		~BinaryTree() { clear(); }

		// ����������� �����������
		BinaryTree(const BinaryTree& other) { root = new Node(*other.root); }

		BinaryTree& operator= (const BinaryTree& other) {
			root = new Node(*other.root);
			return *this;
		}

		// ����������� �����������
		BinaryTree(BinaryTree&& other) noexcept : root(other.root) { other.root = NULL; }

		// ������������ ������� ������ �������� ���
		BinaryTree(const WeightString& avalue) {
			root = new Node(avalue);
		}

		BinaryTree(Node* anode) {
			root = anode;
		}

		// ����� �� ��������� ��������� � ����������� �������� 
		// �������� ������� ��������
		static BinaryTree merge(BinaryTree& l, BinaryTree& r) {
			Node* node = new Node({ 
				// ����������� ����� ������� �� �� ��� �� ������ �� ����� ������ ���������
				// ��������� ������������� �� ����� �������
				l.root->value.first + r.root->value.first,   
				l.root->value.second + r.root->value.second 
			});
			node->leftChild = l.root;
			node->rightChild = r.root;

			// �������� ���� ��������� �������� ����� ��� �� ��������� ������������
			l.root = NULL;
			r.root = NULL;

			return BinaryTree(node);
		}

		// ������� ������
		void clear(Node* node) {
			if (!node) return;

			// ����������� ����� ��� ���� �����������
			clear(node->leftChild);
			clear(node->rightChild);

			delete node;
		}
		void clear() { clear(root); }
	};

	// ����������� ������� ��������� �������� �����
	HuffmanEncoder(const std::string& fname, int shift = 0) : m_finname(fname), m_shift(shift) {}

	// ����� ������� ���������� �������������� ����� � �������� ����
	void writeToBinary(const std::string& fname);
	// ��� ���������� ��� �������� ��������
	void encode();
	// ��������������� ������� ������� ������� ������� � ��������
	void printTable();

private:
	// ��������������� ������� ������� ���������� �������
	void writeTable(BitsWriter& bw);
	// ��������������� ������� ������� ���������� �����
	void writeEncodedText(BitsWriter& bw);

	// ����� ��������� ������ � �������� �������� ����� ������� ������� � ������
	void traversal(BinaryTree::Node* node, std::string code = "");

	// ������ �������� ���������� ����� �� �������� ������ ������
	std::string m_finname;
	// ����� ������� ����� ���������� ����� ������ ������ ������ ������� ����� ������������
	int m_shift;
	// ���-������� ����� ��������
	CodesTable m_codesTable;
};

// ��������� ��������� ������ ������ greater ������� ���������� ��� ������ �� ������� �� �����
// ������������ � std::priority_queue
namespace std {
	template <>
	struct greater<HuffmanEncoder::BinaryTree> {
		constexpr bool operator() (const HuffmanEncoder::BinaryTree& lhs, const HuffmanEncoder::BinaryTree& rhs) const;
	};
}