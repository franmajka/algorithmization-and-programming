#include "Speciality.h"

#include <iostream>
#include <iomanip>

#include <fstream>

#include "stringToBinary.h"

#define NUMBER_OF_SPECIALITIES 12

using namespace std;

const pair<uint16_t, string> SPECIALITIES[NUMBER_OF_SPECIALITIES] = {
	{11, "Науки про освiту"},
	{12, "Дошкiльна освiта"},
	{13, "Початкова освiта"},
	{14, "Середня освiта"},
	{15, "Професiйна освiта"},
	{16, "Спецiальна освiта"},
	{17, "Фiзична культура i спорт"},
	{121, "Iнженерiя програмного забезпечення"},
	{122, "Комп’ютернi науки та iнформацiйнi технологiї"},
	{123, "Комп’ютерна iнженерiя"},
	{124, "Системний аналiз"},
	{125, "Кiбербезпека"},
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
