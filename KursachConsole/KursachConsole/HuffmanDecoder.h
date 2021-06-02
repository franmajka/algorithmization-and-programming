#pragma once

#include <unordered_map>
#include <string>
#include <fstream>
#include <bitset>

class HuffmanDecoder
{
public:
	using CodesTable = std::unordered_map<std::string, char>;

	HuffmanDecoder(const std::string& finname, int shift = 0) : m_finname(finname), m_shift(shift) {}

	void decodeTo(const std::string& foutname);

	void printTable();

private:
	std::string m_finname;
	int m_shift;
	CodesTable m_codesTable;
};

