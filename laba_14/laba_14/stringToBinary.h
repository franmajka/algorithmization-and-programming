#pragma once

#include <cstring>
#include <fstream>

using namespace std;

void swrite(ofstream& fout, const string& str);
void sread(ifstream& fin, string& str);

