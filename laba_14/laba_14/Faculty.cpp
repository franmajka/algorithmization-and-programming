#include "Faculty.h"

#include <iostream>
#include <iomanip>

#include "Speciality.h"
#include "stringToBinary.h"

#define NUMBER_OF_FACULTIES 10

using namespace std;

const string FACULTIES[NUMBER_OF_FACULTIES] = {
	"»œ—¿",
	"‘»Œ“",
	"‘›À",
	"“›‘",
	"‘—œ",
	"’“‘",
	"‘œÃ",
	" ¬œ",
	"»¿“",
	"‘“»",
};

Faculty::Faculty() {
	name = FACULTIES[rand() % NUMBER_OF_FACULTIES];
	
	short numberOfSpecialities = 1 + (rand() % 5);

	for (short i = 0; i < numberOfSpecialities; i++) {
		specialities.pushBack({ Speciality(), 120 + (rand() % 81) });
	}
}

void Faculty::write(std::ofstream& fout) const
{
	swrite(fout, name);

	size_t size = specialities.size();
	fout.write((char*)&size, sizeof(size));

	for (const pair<Speciality, float>& p : specialities) {
		p.first.write(fout);
		fout.write((char*)&p.second, sizeof(p.second));
	}
}

void Faculty::read(std::ifstream& fin)
{
	sread(fin, name);

	size_t size;
	fin.read((char*)&size, sizeof(size));

	specialities.clear();

	for (size_t i = 0; i < size; i++) {
		pair<Speciality, float> p;

		p.first.read(fin);
		fin.read((char*)&p.second, sizeof(p.second));

		specialities.pushBack(p);
	}
}

float Faculty::getAveragePassingScore() const
{
	if (!specialities.size()) return 0;

	float accumulatedPassingScore = 0;

	for (const pair<Speciality, float>& spec : specialities) {
		accumulatedPassingScore += spec.second;
	}

	return accumulatedPassingScore / specialities.size();
}

ostream& operator<<(ostream& out, const Faculty& fac) {
	out << "‘‡ÍÛÎ¸ÚÂÚ ó " << fac.name << endl
		<< "—ÔËÒÓÍ ÒÔÂˆË‡Î¸ÌÓÒÚÂÈ Ò Ëı ÔÓıÓ‰Ì˚ÏË ·‡ÎÎ‡ÏË:" << endl;

	out << fac.specialities;

	return out;
}

