#ifndef CREATE_PENSUM_H
#define CREATE_PENSUM_H

#include <string>
#include <fstream>
#include <iostream>
#include "Materia.h"
#include "Estudiante.h"

using namespace std;

class CreatePensum
{
public:
	CreatePensum(void);
	void addCareer();
	void extractTextFile(string);
	void readPensum(string);
	void readRegister(string, estudianteMemo*);
	void addHijos(string, char[4][10], char[10]);
	void printPensum(string);
};
#endif