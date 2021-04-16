#pragma once

#include <string>
#include "LinkedList.h"

struct Speciality
{
	uint16_t code;
	std::string name;

	Speciality();
	Speciality(const uint16_t&, const std::string&);

	void write(std::ofstream& fout) const;
	void read(std::ifstream& fin);

	friend std::ostream& operator<< (std::ostream&, const Speciality&);
	friend std::ostream& operator<< (std::ostream&, const LinkedList<std::pair<Speciality, float>>&);
};

