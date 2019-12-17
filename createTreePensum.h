#ifndef CREATE_TREE_PENSUM_H
#define CREATE_TREE_PENSUM_H

#include "Materia.h"
#include "Estudiante.h"
#include "createPensum.h"

class createTreePensum
{
private:
	bool isEmpty();
	void searchRec(materiaMemo*, materiaMemo*, char*);
	void printRec(materiaMemo*);
	char* passCode(char[], char[]);
	char* passName(char[], char[]);

public:
	materiaMemo** raiz = 0;
	int cantBloques = 0;
	void printTree(materiaMemo*);
	void recorrerArbol(materiaMemo*, estudianteMemo*);
	void buscar(char*, materiaMemo*);
	bool alreadyExists(materiaMemo*, materiaMemo*);
	void pointerArrayHijos(char[4][10], int);
	materiaMemo* convert(materia);
	materiaMemo* convert2(materia, estudianteMemo*);
	void addClass(materiaMemo*);
	void crearEstudiante();
	void loginEstudiante();
	bool verifEstudiante(int);
	void matriculaClase(estudianteMemo*);
	void matriculaClase(int);
	bool searchPadre(string, string);
	materiaMemo* returnPadre(string, string);
	estudianteMemo* convertirEstudiante(int);
	void treeRegister(materiaMemo*, estudianteMemo*);
	void saveNota(int, double, string);
	void informacionAcademica();
	void promedio(int);
	double getPromedio(int);
	void setClasesAprobadas(int);
	int getClasesAprobadas(int);
	void createNotasFile(int);
	void addClassCreateFile(int, string, double, int);
	bool readDIR(string xKeyWord);
	bool searchClase(string, string);
	void printMatricular(materiaMemo*);
};
#endif