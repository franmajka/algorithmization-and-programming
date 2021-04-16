#include "stringToBinary.h"

void swrite(ofstream& fout, const string& str)
{
	size_t length = str.length() + 1;
	fout.write((char*)&length, sizeof(length));
	fout.write((char*)str.c_str(), length);
}

void sread(ifstream& fin, string& str)
{
	size_t length;
	fin.read((char*)&length, sizeof(length));
	char* buffer = new char[length];

	fin.read(buffer, length);
	str = buffer;

	delete[] buffer;
}
