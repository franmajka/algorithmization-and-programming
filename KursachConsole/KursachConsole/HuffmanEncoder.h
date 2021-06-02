#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

#include "BitsWriter.h"

using WeightTable = std::unordered_map<char, unsigned>;

// Функция которая подсчитывает частоту каждого символов в тексте
WeightTable countSymbols(std::ifstream& fin);

class HuffmanEncoder
{
public:
	// Объявления которые облегчат код
	using WeightString = std::pair<std::string, unsigned>;
	using CodesTable = std::unordered_map<char, std::string>;

	// Всопомогательная структура бинарного дерева
	struct BinaryTree
	{
		// Узел бинарного дерева
		// Листья будут хранить в себе символ и его частоту в тексте
		struct Node {
			WeightString value;

			Node* leftChild = NULL;
			Node* rightChild = NULL;

			Node() : leftChild(NULL), rightChild(NULL) {}
			Node(const WeightString& avalue) : Node() {
				value = avalue;
			}

			// Конструктор копирования
			Node(const Node& anode) {
				value = anode.value;

				leftChild = anode.leftChild ? new Node(*anode.leftChild) : NULL;
				rightChild = anode.rightChild ? new Node(*anode.rightChild) : NULL;
			}
		};

		// Корень дерева
		Node* root;

		// Дефолтный конструктор и деструктор
		BinaryTree() : root(NULL) {};
		~BinaryTree() { clear(); }

		// Конструктор копирования
		BinaryTree(const BinaryTree& other) { root = new Node(*other.root); }

		BinaryTree& operator= (const BinaryTree& other) {
			root = new Node(*other.root);
			return *this;
		}

		// Конструктор перемещения
		BinaryTree(BinaryTree&& other) noexcept : root(other.root) { other.root = NULL; }

		// Конструкторы которые слегка облегчат код
		BinaryTree(const WeightString& avalue) {
			root = new Node(avalue);
		}

		BinaryTree(Node* anode) {
			root = anode;
		}

		// Одним из важнейших действией в кодировании Хаффмана 
		// является слияние деревьев
		static BinaryTree merge(BinaryTree& l, BinaryTree& r) {
			Node* node = new Node({ 
				// Объединение строк которое ни на что не влияет но может слегка облегчить
				// понимания происходящего на этапе отладки
				l.root->value.first + r.root->value.first,   
				l.root->value.second + r.root->value.second 
			});
			node->leftChild = l.root;
			node->rightChild = r.root;

			// Обнуляем руты сливаемых деревьев чтобы они не удалились деструктором
			l.root = NULL;
			r.root = NULL;

			return BinaryTree(node);
		}

		// Очистка дерева
		void clear(Node* node) {
			if (!node) return;

			// Рекурсивный вызов для двух поддеревьев
			clear(node->leftChild);
			clear(node->rightChild);

			delete node;
		}
		void clear() { clear(root); }
	};

	// Конструктор который принимает название файла
	HuffmanEncoder(const std::string& fname, int shift = 0) : m_finname(fname), m_shift(shift) {}

	// Метод который записывает закодированный текст в бинарный файл
	void writeToBinary(const std::string& fname);
	// Тут происходит сам основной алгоритм
	void encode();
	// Вспомогательная функция которая выводит таблицу в коносоль
	void printTable();

private:
	// Вспомогательная функция которая записывает таблицу
	void writeTable(BitsWriter& bw);
	// Вспомогательная функция которая записывает текст
	void writeEncodedText(BitsWriter& bw);

	// Обход бинарного дерева в процессе которого будет создана таблица с кодами
	void traversal(BinaryTree::Node* node, std::string code = "");

	// Храним название тектсового файла из которого читаем данные
	std::string m_finname;
	// Сдвиг который нужно произвести чтобы начать читать данные которые нужно закодировать
	int m_shift;
	// Хеш-таблица кодов символов
	CodesTable m_codesTable;
};

// Добавляем экземпляр шаблна класса greater который сравнивает два дерева по частоте их корня
// Используется в std::priority_queue
namespace std {
	template <>
	struct greater<HuffmanEncoder::BinaryTree> {
		constexpr bool operator() (const HuffmanEncoder::BinaryTree& lhs, const HuffmanEncoder::BinaryTree& rhs) const;
	};
}