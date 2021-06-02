#pragma once

#include <list>
#include <string>

#include "Treap.h"

// ������� ������� ������������ ����� �� ������ � ���������� ��������� ���� + ��� ��� ������ ��� ������ mtf
std::pair<TreapNode*, uint8_t> findInTreap(TreapNode* node, char symb, int key, uint8_t code = 0);
// ������� ������� ���� ��� ���� � ������ ������ ��� ��������
uint8_t getLesserThan(TreapNode* node, int key);

// �������� move-to-front � ����������� ����� treap ���������� �� ������ ����� �������������� ����� � ������
// ���������� ����� �������� + 1 �� ���� ������� ����������� ��� ������������
int mtf(std::string finname, std::string foutname, int shift = 0);

// �������� move-to-front � ����������� ����� ������ �������� ������ ���������
// ���������� ����� �������� + 1 �� ���� ������� ����������� ��� ������������
int mtfSlower(std::string finname, std::string foutname, int shift = 0);

// ������������ ��� move-to-front
void mtfDecode(std::string finname, std::string foutname, int shift = 0);