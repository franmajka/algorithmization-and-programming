#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <clocale>

#include "Student.h"
#include "LinkedList.h"

using namespace std;

LinkedList<Student>* readStudentsFile(string fname) {
	ifstream f(fname);

	if (!f.is_open()) throw "Unable to open file";

	LinkedList<Student> *students = new LinkedList<Student>;

	while (!f.eof()) {
		Student tmp;
		f >> tmp.m_lastName >> tmp.m_firstName >> tmp.m_middleName;
		students->pushBack(tmp);
	}

	f.close();

	return students;
}

void copyStudents(string from, string to) {
	LinkedList<Student> *students = readStudentsFile(from);

	ofstream f(to);

	if (!f.is_open()) throw "Unable to open file";

	while (students->getLength()) {
		Student tmp = students->popFront();
		f << tmp.m_firstName << " " << tmp.m_middleName << " " << tmp.m_lastName << endl;
	}

	f.close();
	delete students;
}

int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "rus");

	string from;
	cout << "Введите название файла из которого нужно копировать" << endl;
	getline(cin, from);

	string to;
	cout << "Введите название файла, в который будут копированы данные" << endl;
	getline(cin, to);

	copyStudents(from, to);

	return 0;
}
