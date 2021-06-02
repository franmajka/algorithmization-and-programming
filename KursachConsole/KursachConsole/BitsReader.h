#pragma once

#include <fstream>
#include <string>

class BitsReader
{
public:
	BitsReader(const std::string& fname);
	~BitsReader();

	std::string read(const uint8_t& quantity);
	void read(char* buff, uint8_t quantity) { m_fin.read(buff, quantity); }

	bool eof() { return m_fin.eof() && byteBuffer == 0; }

	void close();

private:
	std::ifstream m_fin;
	char byteBuffer;
	uint8_t bitsLeft;
};

