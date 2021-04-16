#include "Speciality.h"

#include <iostream>
#include <iomanip>

#include <fstream>

#include "stringToBinary.h"

#define NUMBER_OF_SPECIALITIES 12

using namespace std;

const pair<uint16_t, string> SPECIALITIES[NUMBER_OF_SPECIALITIES] = {
	{11, "����� ��� ���i��"},
	{12, "����i���� ���i��"},
	{13, "��������� ���i��"},
	{14, "������� ���i��"},
	{15, "������i��� ���i��"},
	{16, "����i����� ���i��"},
	{17, "�i����� �������� i �����"},
	{121, "I������i� ����������� ������������"},
	{122, "���������i ����� �� i�������i��i ��������i�"},
	{123, "���������� i������i�"},
	{124, "��������� ����i�"},
	{125, "�i����������"},
};

Speciality::Speciality() {
	const pair<uint16_t, string> p = SPECIALITIES[rand() % NUMBER_OF_SPECIALITIES];
	code = p.first;
	name = p.second;
}

Speciality::Speciality(const uint16_t& acode, const string& aname) {
	code = acode;
	name = aname;
}

void Speciality::write(ofstream& fout) const
{
	fout.write((char*)&code, sizeof(code));
	swrite(fout, name);
}

void Speciality::read(std::ifstream& fin)
{
	fin.read((char*)&code, sizeof(code));
	sread(fin, name);
}

ostream& operator<<(ostream &out, const Speciality &spec) {
	out << setw(3) << setfill('0') << spec.code << " " << spec.name;
	return out;
}

ostream& operator<<(ostream& out, const LinkedList<pair<Speciality, float>>& specs)
{
	int maxNameWidth = 0;

	for (const pair<Speciality, float>& spec : specs) {
		if (spec.first.name.size() > maxNameWidth) maxNameWidth = spec.first.name.size();
	}

	for (const pair<Speciality, float>& spec : specs) {
		out << "  " << setw(3) << setfill('0') << spec.first.code << " ";
		out << setw(maxNameWidth) << setfill(' ') << left << spec.first.name
			<< " : " << spec.second << endl;
		out << right;
	}

	return out;
}
