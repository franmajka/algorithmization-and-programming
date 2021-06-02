#pragma once

#include <fstream>
#include <string>

// Запись битов и байтов не связана а так как биты пишутся через буффер запись 
// сначала нескольких битов а затем байтов приведет к тому что байты запишутся без
// очереди а потом когда накопится нужное количество битов либо файл закроется запишутся биты
// У меня не было потребности в перемежной записи битов и байтов так что я не стал усложнять код
class BitsWriter
{
public:
	BitsWriter(const std::string& fname);
	~BitsWriter();

	// Запись битов
	void write(const std::string& bits);
	void close();

	int tellp() { return m_fout.tellp(); }
	void seekp(int pos) { m_fout.seekp(pos); }

	// Запись байтов
	void write(const char* bytes, unsigned length) { m_fout.write(bytes, length); }

private:
	char byteBuffer;
	uint8_t currentlyWritten;
	std::ofstream m_fout;
};

