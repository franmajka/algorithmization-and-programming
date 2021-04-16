#include "InstitutesList.h"
#include "Institute.h"

#include <fstream>

using namespace std;

InstitutesList::InstitutesList(std::string fname)
{
	m_fname = fname;
	ifstream fin(m_fname);
	if (fin.is_open() && !fin.eof()) read(fin);
	fin.close();
}

InstitutesList::~InstitutesList()
{
	ofstream fout(m_fname);
	write(fout);
	fout.close();
}

void InstitutesList::sortByPassingScore()
{
	m_institutes.sort(
		[](const Institute& left, const Institute& right) {
			return left.getAveragePassingScore() < right.getAveragePassingScore();
		}
	);
}

Institute InstitutesList::findByPassingScore(float pScore) const
{
	for (const Institute& institute : m_institutes) {
		if (fabs(pScore - institute.getAveragePassingScore()) < 1e-5) {
			return institute;
		}
	}

	throw "There're no institute with the passing score";
}

LinkedList<pair<Speciality, float>> InstitutesList::getSpecialitiesInRange(float from, float to)
{
	LinkedList<pair<Speciality, float>> specs;

	for (const Institute& institute : m_institutes) {
		for (const Faculty& fac : institute.faculties) {
			for (const pair<Speciality, float>& spec : fac.specialities) {
				if (from <= spec.second && spec.second <= to) 
					specs.pushBack(spec);
			}
		}
	}

	return specs;
}

Institute InstitutesList::pop(size_t idx)
{
	return m_institutes.pop(idx);
}

void InstitutesList::append(const Institute& institute)
{
	m_institutes.pushBack(institute);
}

void InstitutesList::write(ofstream& fout)
{
	size_t size = m_institutes.size();
	fout.write((char*)&size, sizeof(size));

	for (const Institute& institute : m_institutes) {
		institute.write(fout);
	}
}

void InstitutesList::read(ifstream& fin)
{
	size_t size;
	fin.read((char*)&size, sizeof(size));

	m_institutes.clear();

	for (size_t i = 0; i < size; i++) {
		Institute institute;
		institute.read(fin);
		m_institutes.pushBack(institute);
	}
}

ostream& operator<<(ostream& out, const InstitutesList& institutesList)
{
	out << "Ñïèñîê èíñòèòóòîâ:" << endl << endl << "———————" << endl << endl;
	for (const Institute& institute : institutesList.m_institutes) {
		out << institute << "———————" << endl << endl;
	}
	return out;
}
