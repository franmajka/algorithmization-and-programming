#include "Institute.h"

#include "Faculty.h"

#include <cstring>
#include <iostream>

#include "stringToBinary.h"

#define NUMBER_OF_INSTITUTE_NAMES 8
#define NUMBER_OF_INSTITUTE_PLANS 3

using namespace std;

const string INSTITUTE_NAMES[NUMBER_OF_INSTITUTE_NAMES] = {
	"KПИ",
	"УКУ",
	"КНЕУ",
	"ХНУРЕ",
	"ХНУ",
	"КНУТШ",
	"НАУ",
	"Могилянка",
};

const string INSTITUTE_PLANS[NUMBER_OF_INSTITUTE_PLANS] = {
	"Делаем вид что нам не все равно.",
	"Скидываем все на абит отдел там разберутся.",
	"Кому вообще нужны перваши?",
};

void Institute::write(std::ofstream& fout) const
{
	swrite(fout, name);
	swrite(fout, admissionPlan);

	size_t size = faculties.size();
	fout.write((char*)&size, sizeof(size));

	for (const Faculty& fac : faculties) {
		fac.write(fout);
	}
}

void Institute::read(std::ifstream& fin)
{
	sread(fin, name);
	sread(fin, admissionPlan);

	size_t size;
	fin.read((char*)&size, sizeof(size));

	faculties.clear();

	for (size_t i = 0; i < size; i++) {
		Faculty tmp;
		tmp.read(fin);
		faculties.pushBack(tmp);
	}
}

float Institute::getAveragePassingScore() const
{
	if (!faculties.size()) return 0;

	float accumulatedPassingScore = 0;

	for (const Faculty& fac : faculties) {
		accumulatedPassingScore += fac.getAveragePassingScore();
	}

	return accumulatedPassingScore / faculties.size();
}

Institute::Institute()
{
	name = INSTITUTE_NAMES[rand() % NUMBER_OF_INSTITUTE_NAMES];
	admissionPlan = INSTITUTE_PLANS[rand() % NUMBER_OF_INSTITUTE_PLANS];

	for (int i = 1 + (rand() % 4); i >= 0; i--) faculties.pushBack(Faculty());
}

std::ostream& operator<<(std::ostream& out, const Institute& institute)
{
	out << "Институт — " << institute.name << endl;
	out << "Список факультетов:" << endl << endl;

	for (const Faculty& fac : institute.faculties) {
		out << fac << endl;
	}

	return out;
}
