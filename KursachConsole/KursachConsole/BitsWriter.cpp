#include "BitsWriter.h"

#include <fstream>
#include <string>

#define BYTE_LENGTH 8

using namespace std;

BitsWriter::BitsWriter(const std::string& fname)
{
	byteBuffer = 0;
	currentlyWritten = 0;

	m_fout = ofstream(fname, ios::binary);
}

BitsWriter::~BitsWriter()
{
	if (m_fout.is_open()) close();
}

void BitsWriter::write(const std::string& bits)
{
	for (const char& c : bits) {
		byteBuffer |= c == '1';
		currentlyWritten = (currentlyWritten + 1) % BYTE_LENGTH;

		if (!currentlyWritten) {
			m_fout.write(&byteBuffer, 1);
			byteBuffer = 0;
			continue;
		}

		byteBuffer <<= 1;
	}
}

void BitsWriter::close()
{
	if (currentlyWritten) {
		write(string(BYTE_LENGTH - currentlyWritten, '0'));
	}
	m_fout.close();
}
