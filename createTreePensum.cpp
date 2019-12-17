#include "createTreePensum.h"
#include <iostream>
#include <fstream>
#include <list>
#include <dirent.h>

using namespace std;
using std::cout;

bool createTreePensum::isEmpty()
{
	return raiz == 0;
}

void createTreePensum::searchRec(materiaMemo* raiz,materiaMemo* actTemp, char* codigoPadre)
{
	if (isEmpty())
	{
		return;
	}

	for (int i = 0; i < raiz->cantPadres; i++)
	{
		string check = codigoPadre;
		if (raiz->codigo == check)
		{
			if (alreadyExists(actTemp, raiz) == false)
			{
				materiaMemo** temp = new materiaMemo * [actTemp->cantHijos + 1];

				for (int i = 0; i < actTemp->cantHijos; i++)
				{
					temp[i] = actTemp->hijos[i];
				}
				temp[actTemp->cantHijos] = actTemp;

				if (actTemp->cantHijos != 0)
				{
					delete actTemp->hijos;
				}
				actTemp->hijos = temp;
				actTemp->cantHijos++;
				return;
			}
			
		}
		for (int i = 0; i < raiz->cantHijos; i++)
		{
			searchRec(raiz->hijos[i], actTemp, codigoPadre);
		}
	}
	return;
}

void createTreePensum::printRec(materiaMemo* raiz)
{
	if (isEmpty())
	{
		return;
	}
	cout << "Materia { codigo: " << raiz->codigo << ", nombre: " << raiz->nombre << " }\n";
	for (int i = 0; i < raiz->cantHijos; i++)
	{
		
	}
}

char *createTreePensum::passCode(char codeArray[], char arrayCpy[])
{
	for (int i = 0; i < 30; i++)
	{
		codeArray[i] = ' ';
	}

	for (int i = 0; i < 30; i++)
	{
		codeArray[i] = arrayCpy[i];
	}
	return codeArray;
}

char *createTreePensum::passName(char nameArray[], char nameArrayCpy[])
{
	for (int i = 0; i < 100; i++)
	{
		nameArray[i] = ' ';
	}

	for (int i = 0; i < 100; i++)
	{
		nameArray[i] = nameArrayCpy[i];
	}

	return nameArray;
}

void createTreePensum::buscar(char* _codigoPadre, materiaMemo* actTemp)
{
	for (int x = 0; x < cantBloques; x++)
	{
		searchRec(raiz[x], actTemp, _codigoPadre);
	}
	
}

bool createTreePensum::alreadyExists(materiaMemo* actual, materiaMemo* raiz)
{
	for (int i = 0; i < actual->cantHijos; i++)
	{
		if (actual == raiz->hijos[i])
		{
			return true;
		}
	}
	return false;
}

void createTreePensum::pointerArrayHijos(char _arr[4][10], int nHijos)
{
	materia** hijosxx = new materia *[nHijos];

	

}

materiaMemo* createTreePensum::convert(materia data)
{
	materiaMemo* actual = new materiaMemo();

	actual->codigo = data.codigo;
	actual->nombre = data.nombre;
	actual->UVs = data.UVs;
	actual->anoP = data.anoP;
	actual->periodo = data.periodo;
	actual->UVsRequisito = data.UVsRequisito;

	for (int i = 0; i < 4; i++)
	{
		string padre;
		string as = data.padres[i];
		for (int j = 0; j < as.size(); j++)
		{
			if (data.padres[i][j] != 0)
			{
				padre += data.padres[i][j];
			}
		}
		if (padre != "")
		{
			actual->setpadres((char*)padre.c_str());
		}
	}
	
	addClass(actual);
	return actual;
}

materiaMemo* createTreePensum::convert2(materia data, estudianteMemo* estu)
{
	materiaMemo* actual = new materiaMemo();

	actual->codigo = data.codigo;
	actual->nombre = data.nombre;
	actual->UVs = data.UVs;
	actual->anoP = data.anoP;
	actual->periodo = data.periodo;
	actual->UVsRequisito = data.UVsRequisito;

	for (int i = 0; i < 4; i++)
	{
		string padre;
		string as = data.padres[i];
		for (int j = 0; j < as.size(); j++)
		{
			if (data.padres[i][j] != 0)
			{
				padre += data.padres[i][j];
			}
		}
		if (padre != "")
		{
			actual->setpadres((char*)padre.c_str());
		}
	}

	treeRegister(actual, estu);
	return actual;
}

void createTreePensum::addClass(materiaMemo* materia)
{
	string check = materia->padres[0];
	if (check == "0")
	{
		materiaMemo** temp = new materiaMemo * [cantBloques + 1];
		for (int i = 0; i < cantBloques; i++)
		{
			temp[i] = raiz[i];
		}
		temp[cantBloques] = materia;

		if (raiz != 0)
		{
			delete raiz;
		}
		raiz = temp;
		cantBloques++;
	}
	else
	{
		for (int i = 0; i < materia->cantPadres; i++)
		{
			buscar(materia->padres[i], materia);
		}
	}
	printTree(*raiz);

}

void createTreePensum::crearEstudiante()
{

	fstream file("Estudiantes.dat", ios::out | ios::in | ios:: app | ios::binary);

	estudiante actual;
	cout << "Ingrese nombre: ";
	cin >> actual.nombre;
	cout << "Ingrese numero de cuenta: ";
	cin >> actual.numCuenta;
	cout << "Codigo de plan de estudio: ";
	cin >> actual.nombrePlan;
	actual.clasesAprobadas = 0;
	string path = actual.nombrePlan;
	string searchDir = path + "_plan.dat";
	if (readDIR(searchDir) == true)
	{
		file.write(reinterpret_cast<char*>(&actual), sizeof(estudiante));
		createNotasFile(actual.numCuenta);
		cout << "Estudiante creado exitosamente";
	}
	else
	{
		cout << "Plan no existe";
	}
	
	file.close();
}

void createTreePensum::loginEstudiante()
{
	int numeroCuenta = 0;

	cout << "Ingrese numero de cuenta: ";
	cin >> numeroCuenta;
	estudianteMemo* estux;
	if (verifEstudiante(numeroCuenta) == true)
	{
		int optionz = 0;
		do
		{
			cout << "=== Menu Estudiantil ===" << endl;
			cout << "1. Matricular Materias" << endl;
			cout << "2. Regresar" << endl;
			cin >> optionz;

			if (optionz == 1)
			{
				//matriculaClase(convertirEstudiante(numeroCuenta));
				matriculaClase(numeroCuenta);
			}
			
		} while (optionz!= 2);
	}
	else
	{
		cout << "Numero de cuenta erroneo o no existente!";
		return;
	}
}

bool createTreePensum::verifEstudiante(int codigo)
{
	fstream file("Estudiantes.dat", ios::in | ios::out | ios::binary);

	if (file.fail())
	{
		cout << "Archivo de estudiantes no existente!";
		return false;
	}

	estudiante actual;

	file.seekg(0);
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));

	while (!file.eof())
	{
		if (actual.numCuenta == codigo)
		{
			return true;
		}
		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}

	return false;
}

void createTreePensum::matriculaClase(int codigo)
{
	fstream fileestu("Estudiantes.dat", ios::in | ios::out | ios::binary);

	fileestu.seekg(0);
	estudiante actual;
	string send = "_plan.dat";
	string search = "";
	fileestu.read(reinterpret_cast<char*>(&actual), sizeof(estudiante));

	while (!fileestu.eof())
	{
		if (actual.numCuenta == codigo)
		{
			search = actual.nombrePlan + send;
		}
		fileestu.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}
	fileestu.close();

	CreatePensum* pensum = new CreatePensum();
	pensum->readPensum(search);
	
	cout << "\nIngrese cantidad de clases a matricular: ";
	int cant = 0;
	cin >> cant;

	if (cant <= 3)
	{
		for (int i = 0; i < cant; i++)
		{
			string codeClassX = "";
			cout << "\nIngrese codigo de clase a matricular: ";
			cin >> codeClassX;
			string af = codeClassX + "_plan.dat";
			if (searchClase(search, codeClassX) == true)
			{
				materiaMemo* uss = new materiaMemo();
				uss = returnPadre(codeClassX, search);
				cout << "\nIngrese nota: ";
				double nota = 0;
				cin >> nota;

				addClassCreateFile(codigo, codeClassX, nota, uss->UVs);
			}
			else
			{
				cout << "Clase no existente";
				return;
			}


		}
	}
	else
	{
		cout << "Maximo de tres clases a matricular." << endl;
		return;
	}
	
	
}

bool createTreePensum::searchPadre(string filename, string nombreClase)
{
	fstream file(filename, ios::in | ios::out | ios::binary);

	materia actual;

	file.seekg(sizeof(metaData));
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));

	while (!file.eof())
	{
		if (actual.nombre == nombreClase)
		{
			if (actual.nota >= 60)
			{
				file.close();
				return true;
			}
			else
			{
				file.close();
				return false;
			}
		}
		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}
}

materiaMemo* createTreePensum::returnPadre(string codigoClase, string filename)
{
	fstream file(filename, ios::out | ios::in | ios::binary);

	materia actual;
	materiaMemo* nuevo = new materiaMemo();
	file.seekg(sizeof(metaData));
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));

	while (!file.eof())
	{
		if (actual.codigo == codigoClase)
		{
			nuevo = convert(actual);
		}
		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}
	return nuevo;
}

estudianteMemo* createTreePensum::convertirEstudiante(int codigo)
{
	fstream file("Estudiantes.dat", ios::in | ios::out | ios::binary);

	if (file.fail())
	{
		cout << "Archivo de estudiantes no existente!";
		return 0;
	}

	estudiante actual;

	file.seekg(0);
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	estudianteMemo* estu = new estudianteMemo();
	while (!file.eof())
	{
		if (actual.numCuenta == codigo)
		{
			estu->nombre = actual.nombre;
			estu->numCuenta = actual.numCuenta;
			estu->nombrePlan = actual.nombrePlan;
			estu->indice = actual.indice;
			estu->clasesAprobadas = actual.clasesAprobadas;
		}
		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}
	return estu;

}

void createTreePensum::treeRegister(materiaMemo* materia, estudianteMemo* estu)
{
	string check = materia->padres[0];

	if (check == "0")
	{
		materiaMemo** temp = new materiaMemo * [cantBloques + 1];
		for (int i = 0; i < cantBloques; i++)
		{
			temp[i] = raiz[i];
		}
		temp[cantBloques] = materia;

		if (raiz != 0)
		{
			delete raiz;
		}
		raiz = temp;
		cantBloques++;
	}
	else
	{
		for (int i = 0; i < materia->cantPadres; i++)
		{
			buscar(materia->padres[i], materia);
		}
	}
	recorrerArbol(*raiz, estu);
}

void createTreePensum::saveNota(int codigo, double nota, string filename)
{
	fstream file("Estudiantes.dat", ios::in | ios::out | ios::binary);
	if (file.fail())
	{
		cout << "could not open file!";
		return;
	}
	estudiante actual;
	file.seekg(0);
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));

	while (!file.eof())
	{
		if (actual.numCuenta == codigo)
		{
			actual.indice += nota;
			file.write(reinterpret_cast<char*>(&actual), sizeof(materia));
			file.close();
			return;
		}
		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}
	file.close();
}

void createTreePensum::informacionAcademica()
{
	int codigoEstu = 0;
	cout << "Ingrese numero de cuenta: ";
	cin >> codigoEstu;
	bool check = false;
	fstream fileestu("Estudiantes.dat", ios::in | ios::out | ios::binary);

	fileestu.seekg(0);
	estudiante actual;
	string send = "_plan.dat";
	string search = "";
	fileestu.read(reinterpret_cast<char*>(&actual), sizeof(actual));

	while (!fileestu.eof())
	{
		if (actual.numCuenta == codigoEstu)
		{
			check = true;
		}
		fileestu.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}
	fileestu.close();

	int optionh = 0;
	if (check == true)
	{
		cout << "\n1. Indice Academico";
		cout << "\n2. Clases Aprobadas";
		cout << "\nIngrese opcion: ";
		cin >> optionh;

		if (optionh == 1)
		{
			cout << "\nPromedio: " << getPromedio(codigoEstu);
		}
		else if (optionh == 2)
		{
			cout << "\nCantidad de clases aprobadas: " << getClasesAprobadas(codigoEstu);
		}
		else
		{
			cout << "\nOpcion no valida";
		}
	}
}

void createTreePensum::promedio(int _numCuenta)
{
	fstream file("Estudiantes.dat", ios::out | ios::in | ios::binary);

	estudiante actual;
	file.seekg(0);
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	double nota = 0;
	double promedio = 0;
	double resultPromedio = 0;
	int UVS = 0;
	while (!file.eof())
	{
		if (actual.numCuenta == _numCuenta)
		{
			nota = actual.indice;
			UVS = actual.clasesAprobadas * 4;
			promedio = UVS * nota;
			resultPromedio = promedio / UVS;
			file.write(reinterpret_cast<char*>(&actual), sizeof(estudiante));
		}
		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}
	return;
}

double createTreePensum::getPromedio(int _numCuenta)
{
	string af = to_string(_numCuenta);
	fstream file(af+"_NotasFile.dat", ios::out | ios::in | ios::binary);

	if (file.fail())
	{
		cout << "Error opening file";
		return 0;
	}
	notas actual;
	double notas = 0;
	double promedio = 0;
	int _UVS = 0;
	int cantClases = 0;
	file.seekg(0);
	file.seekg(sizeof(code));
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	while (!file.eof())
	{
		notas += (actual.notaClase * 4);
		_UVS += 4;
		cantClases++;
		file.read(reinterpret_cast<char*>(&actual), sizeof(notas));
	}
	file.close();
	promedio = notas / _UVS;
	return promedio;
}

void createTreePensum::setClasesAprobadas(int _numCuenta)
{
	fstream file("Estudiantes.dat", ios::out | ios::in | ios::binary);

	estudiante actual;
	file.seekg(0);
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	double nota = 0;
	double promedio = 0;
	int UVS = 0;
	while (!file.eof())
	{
		if (actual.numCuenta == _numCuenta)
		{
			actual.clasesAprobadas++;
			file.write(reinterpret_cast<char*>(&actual), sizeof(estudiante));
		}
		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}
}

int createTreePensum::getClasesAprobadas(int _numCuenta)
{
	string as = to_string(_numCuenta);
	fstream file(as+"_NotasFile.dat", ios::out | ios::in | ios::binary);
	
	int result = 0;
	notas actual;
	file.seekg(sizeof(code));
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	
	while (!file.eof())
	{
		double compare = actual.notaClase;
		if (compare > 60)
		{
			result++;
		}
		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}
	return result;
}

void createTreePensum::createNotasFile(int numCuenta)
{
	string af = to_string(numCuenta);
	string carpeta = "C:\\Users\\aaron\\source\\repos\\University_Registration_System\\University_Registration_System\\" + af;
	string ext = "_NotasFile.dat";
	fstream file(carpeta + ext, ios::out | ios::app | ios::binary);
	
	if (file.fail())
	{
		cout << "bruh";
	}
	file.seekg(0);
	
	code actual;

	actual.codex = numCuenta;

	file.write(reinterpret_cast<char*>(&actual), sizeof(code));
	file.close();
}

void createTreePensum::addClassCreateFile(int numCuenta, string nombreClase, double nota, int UV)
{
	string as = to_string(numCuenta);
	fstream file(as+"_NotasFile.dat", ios::in | ios::out | ios::app | ios::binary);
	notas actual;

	for (int i = 0; i < nombreClase.size(); i++)
	{
		actual.nombreClase[i] = nombreClase[i];
	}
	actual.notaClase = nota;

	file.write(reinterpret_cast<char*>(&actual), sizeof(notas));
	file.close();
}

void createTreePensum::printTree(materiaMemo* raiz)
{
	if (raiz == nullptr)
	{
		return;
	}
	//raiz->imprimir();
	cout << "{ Codigo: " << raiz->codigo << ", Nombre: " << raiz->nombre << ", UVs: " << raiz->UVs << ", Anio Periodo: " << raiz->anoP << ", Periodo: " << raiz->periodo << ", UVs Requisito: " << raiz->UVsRequisito << " }";
	cout << '\n';
	for (size_t i = 0; i < raiz->cantHijos; i++)
	{
		printTree(raiz->hijos[i]);
	}
	return;
}

void createTreePensum::recorrerArbol(materiaMemo* raiz, estudianteMemo* estu)
{
	if (raiz == nullptr)
	{
		return;
	}
	//raiz->imprimir();   
	string check = raiz->padres[0];
	if (check == "0")
	{
		if (raiz->pass == 0)
		{
			cout << "Clase: " << raiz->nombre << "| Codigo: " << raiz->codigo << endl;
		}
		
	}
	else
	{
		int checkReg = 0;
		string ext = "_plan.dat";
		if (raiz->pass == 0)
		{
			for (int i = 0; i < raiz->cantPadres; i++)
			{
				string padrex = raiz->padres[i];
				if (searchPadre(estu->nombrePlan + ext, padrex) == false)
				{
					cout << "Clase: " << raiz->nombre << ", |Codigo: " << raiz->codigo << endl;
				}
			}
		}
	}
	for (size_t i = 0; i < raiz->cantHijos; i++)
	{
		recorrerArbol(raiz->hijos[i], estu);
	}
	return;
}

bool createTreePensum::readDIR(string xKeyWord)
{
	DIR* dir;
	struct dirent* ent;
	if ((dir = opendir("C:\\Users\\aaron\\source\\repos\\University_Registration_System\\University_Registration_System\\")) != NULL) {
		/* print all the files and directories within directory */
		while ((ent = readdir(dir)) != NULL) {
			//printf("%s\n", ent->d_name);
			if (xKeyWord == ent->d_name)
			{
				return true;
			}
		}
	}
	else {
		/* could not open directory */
		perror("Something went wrong");
		return false;
	}
}

bool createTreePensum::searchClase(string filename, string clase)
{
	fstream file(filename, ios::in | ios::out | ios::binary);

	if (file.fail())
	{
		cout << "Error opening file";
		return false;
	}

	materia actual;
	file.seekg(sizeof(metaData));
	file.read(reinterpret_cast<char*>(&actual), sizeof(materia));

	while (!file.eof())
	{
		if (actual.codigo == clase)
		{
			return true;
		}
		file.read(reinterpret_cast<char*>(&actual), sizeof(materia));
	}
	return false;
}
