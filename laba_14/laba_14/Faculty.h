#pragma once

#include <string>

#include "LinkedList.h"
#include "Speciality.h"

struct Faculty
{
	std::string name;
	LinkedList<std::pair<Speciality, float>> specialities;

	Faculty();

	void write(std::ofstream& fout) const;
	void read(std::ifstream& fin);

	float getAveragePassingScore() const;

	friend std::ostream& operator<< (std::ostream&, const Faculty&);
};

