#include "BitsReader.h"

#include <fstream>
#include <string>

#define BYTE_LENGTH 8

using namespace std;

BitsReader::BitsReader(const std::string& fname)
{
	bitsLeft = 0;
	byteBuffer = 0;

	m_fin = ifstream(fname, ios::binary);
}

BitsReader::~BitsReader()
{
	if (m_fin.is_open()) close();
}

string BitsReader::read(const uint8_t& quantity)
{
	string bits = "";

	for (uint8_t i = 0; i < quantity; i++) {
		if (!bitsLeft) {
			if (m_fin.eof()) return bits;
			m_fin.read(&byteBuffer, 1);
			bitsLeft = BYTE_LENGTH;
		}

		bits += byteBuffer & 0b10000000 ? '1' : '0';
		byteBuffer <<= 1;
		bitsLeft -= 1;
	}

	return bits;
}

void BitsReader::close()
{
	m_fin.close();
}
