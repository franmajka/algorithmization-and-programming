#pragma once

#include <map>
#include <list>
#include <fstream>
#include <string>

#include "LongDecimal.h"

class Range {
public:
	Range(const LongDecimal& low, const LongDecimal& high, unsigned char c) : m_low(low), m_high(high), m_c(c) {}
	std::list<Range> split(const std::map<unsigned char, LongDecimal>& probabilities) const;

	bool includes(const LongDecimal& n) const { return m_low <= n && n < m_high; }
	bool includes(char c) const { return m_c == c; }

	const LongDecimal& getLow() const { return m_low; }
	const LongDecimal& getHigh() const { return m_high; }
	unsigned char getC() const { return m_c; }

private:
	LongDecimal m_low;
	LongDecimal m_high;
	char m_c;
};

std::map<unsigned char, LongDecimal> getProbabilities(std::ifstream& fin);
unsigned arithmeticEncode(std::string finname, std::string foutname, unsigned shift = 0);
void arithmeticDecode(std::string finname, std::string foutname, unsigned shift = 0);