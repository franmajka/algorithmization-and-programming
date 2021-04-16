#pragma once

#include "Institute.h"
#include "Speciality.h"
#include "LinkedList.h"

class InstitutesList
{
public:
	InstitutesList(std::string fname);
	~InstitutesList();

	void sortByPassingScore();
	Institute findByPassingScore(float pScore) const;
	LinkedList<std::pair<Speciality, float>> getSpecialitiesInRange(float from, float to);

	Institute pop(size_t idx);
	void append(const Institute& institute);

	friend std::ostream& operator<< (std::ostream& out, const InstitutesList& institutesList);
private:
	void write(std::ofstream& fout);
	void read(std::ifstream& fin);

	LinkedList<Institute> m_institutes;
	std::string m_fname;
};

