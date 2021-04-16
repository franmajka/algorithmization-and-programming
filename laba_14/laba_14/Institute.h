#pragma once

#include <string>

#include "Faculty.h"
#include "LinkedList.h"

struct Institute
{
	std::string name;
	std::string admissionPlan;
	LinkedList<Faculty> faculties;

	void write(std::ofstream& fout) const;
	void read(std::ifstream& fin);

	float getAveragePassingScore() const;

	Institute();

	friend std::ostream& operator<< (std::ostream&, const Institute&);
};

