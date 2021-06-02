#pragma once

#include <fstream>
#include <string>

// ������ ����� � ������ �� ������� � ��� ��� ���� ������� ����� ������ ������ 
// ������� ���������� ����� � ����� ������ �������� � ���� ��� ����� ��������� ���
// ������� � ����� ����� ��������� ������ ���������� ����� ���� ���� ��������� ��������� ����
// � ���� �� ���� ����������� � ���������� ������ ����� � ������ ��� ��� � �� ���� ��������� ���
class BitsWriter
{
public:
	BitsWriter(const std::string& fname);
	~BitsWriter();

	// ������ �����
	void write(const std::string& bits);
	void close();

	int tellp() { return m_fout.tellp(); }
	void seekp(int pos) { m_fout.seekp(pos); }

	// ������ ������
	void write(const char* bytes, unsigned length) { m_fout.write(bytes, length); }

private:
	char byteBuffer;
	uint8_t currentlyWritten;
	std::ofstream m_fout;
};

