#pragma once

#include <list>
#include <string>

#include "Treap.h"

// Функция которая осуществляет поиск по дереву и возвращает найденный узел + его код нужный для работы mtf
std::pair<TreapNode*, uint8_t> findInTreap(TreapNode* node, char symb, int key, uint8_t code = 0);
// Функция которая ищет все узлы с ключем меньше чем аргумент
uint8_t getLesserThan(TreapNode* node, int key);

// Алгоритм move-to-front с реализацией через treap записывает из одного файла закодированный текст в другой
// Возвращает длину алфавита + 1 то есть символы необходимые для раскодировки
int mtf(std::string finname, std::string foutname, int shift = 0);

// Алгоритм move-to-front с реализацией через список работает слегка медленнее
// Возвращает длину алфавита + 1 то есть символы необходимые для раскодировки
int mtfSlower(std::string finname, std::string foutname, int shift = 0);

// Декодировщик для move-to-front
void mtfDecode(std::string finname, std::string foutname, int shift = 0);