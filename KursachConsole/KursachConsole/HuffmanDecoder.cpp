#include "HuffmanDecoder.h"

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <bitset>

#include "BitsReader.h"

#define BYTE_LENGTH 8

using namespace std;

void HuffmanDecoder::decodeTo(const string& foutname)
{
	m_codesTable.clear();

	ofstream fout(foutname, ios::binary);
	BitsReader br(m_finname);

	char buffer;
	for (int i = 0; i < m_shift; i++) {
		buffer = bitset<8>(br.read(BYTE_LENGTH)).to_ulong();
		fout.write(&buffer, 1);
	}

	uint8_t tableSize = bitset<BYTE_LENGTH>(br.read(BYTE_LENGTH)).to_ulong();

	for (uint8_t i = 0; i < tableSize; i++) {
		char c = bitset<BYTE_LENGTH>(br.read(BYTE_LENGTH)).to_ulong();
		uint8_t codeLength = bitset<BYTE_LENGTH>(br.read(BYTE_LENGTH)).to_ulong();
		m_codesTable.insert({ br.read(codeLength), c });
	}

	while (true) {
		string bits;
		auto found = m_codesTable.find(bits);
		do {
			string bit = br.read(1);
			// No \0 at the end
			// Probably broken file
			if (bit == "") {
				throw "Not valid file input";
			}

			bits += bit;
			found = m_codesTable.find(bits);
		} while (found == m_codesTable.end());

		if (found->second == 0) break;
		fout.write(&found->second, 1);
	}

	fout.close();
	br.close();
}

void HuffmanDecoder::printTable()
{
	for (const auto& p : m_codesTable) {
		std::cout << p.first << " - " << p.second << std::endl;
	}
}