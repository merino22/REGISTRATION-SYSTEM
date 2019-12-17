#include "createPensum.h"
#include "createTreePensum.h"
#include <string>
#include <string.h>

using namespace std;

CreatePensum::CreatePensum(void){}

void CreatePensum::addCareer()
{
	metaData objM;

	cout << "Ingrese codigo del plan: ";
	cin >> objM.codigoPlan;
	cout << "Ingrese nombre del plan: ";
	cin >> objM.nombrePlan;
	cout << "Ingrese cantidad total de clases: ";
	cin >> objM.totalClases;
	//cout << "Ingrese cantidad de bloques de conocimiento: ";
	objM.cantBloques = 0;
	string codex = objM.codigoPlan;
	fstream file(codex + "_plan.dat", ios::out | ios::app | ios::binary);

	file.write(reinterpret_cast<char*>(&objM), sizeof(metaData));

	materia obj;
	string padrex;
	createTreePensum obj2;
	file.seekg(0);
	file.seekg(sizeof(metaData));

	obj2.cantBloques = objM.cantBloques;
	for (int n = 0; n < objM.totalClases; n++)
	{
		
		cout << "Input class code: ";
		cin >> obj.codigo;
		cout << "Input name of class: ";
		cin >> obj.nombre;
		cout << "Input class UVs: ";
		cin >> obj.UVs;
		cout << "Input year of period: ";
		cin >> obj.anoP;
		cout << "Input Period: ";
		cin >> obj.periodo;
		cout << "Input amount of parent classes: ";
		int x = 0;
		cin >> x;
		for (int i = 0; i < x; i++)
		{
			cout << "Input required class: ";
			cin >> padrex;

				for (int n = 0; n < padrex.size(); n++)
				{
					obj.padres[i][n] = padrex.at(n);
				}
		}
		file.write(reinterpret_cast<char*>(&obj), sizeof(materia));
		
	}
	file.close();
	printPensum(codex + "_plan.dat");
	readPensum(codex + "_plan.dat");
	//printPensum(codex + "_plan.dat");
	//addHijos(codex + "_plan.dat", obj.padres, nameData);
	//obj2.addClass(codeData, nameData, UVsData, periodYearData, periodData, obj.padres, obj.hijos, obj.nota, obj.UVsRequisito);

	
}

void CreatePensum::extractTextFile(string name)
{
	ifstream file;
	file.open(name);
	string line;
	materia obj;

	if (file.fail())
	{
		cout << "Could not open text file.";
		return;
	}

	while (!file.eof())
	{
		getline(file, line);

		string delimiter("Codigo:");
		size_t pos = 0;
		int x = 0;
		string word = "";
		string save = "";
		bool check = false;
		
		//cout << line << endl;

		for (int i = 0; i < line.size(); i++)
		{
			save = "";
			word += line.at(i);

			if (word == "Codigo:")
			{
				for (int j = i; j < line.length(); j++)
				{
					save += line.at(j);
				}
				cout << save << endl;
			}
			else if (word == "Materia:")
			{
				for (int j = i; j < line.length(); j++)
				{
					save += line.at(j);
				}
				cout << save << endl;
			}
			else if (word == "UVs:")
			{
				for (int j = line.length() - i; j < line.length(); j++)
				{
					save += line.at(j);
				}
				cout << save << endl;
			}
			else if (word == "Ano Plan:")
			{
				for (int j = line.length() - i; j < line.length(); j++)
				{
					save += line.at(j);
				}
				cout << save << endl;
			}
			else if (word == "Periodo:")
			{
				for (int j = line.length() - i; j < line.length(); j++)
				{
					save += line.at(j);
				}
				cout << save << endl;
			}
			else if (word == "Padre:")
			{
				for (int j = line.length() - i; j < line.length(); j++)
				{
					save += line.at(j);
				}
				cout << save << endl;
			}
			//cout << '\n';
		}
	}
}       

void CreatePensum::readPensum(string name)
{
	fstream file;
	file.open(name, ios::in | ios::binary);
	
	if (file.fail())
	{
		cout << "Unable to open file, check file\'s path.";
		return;
	}
	materia actual;
	createTreePensum obj;
	file.seekg(sizeof(metaData));
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));

	materiaMemo* nuevo = new materiaMemo();
	nuevo = obj.convert(actual);
	//obj.addClass(nuevo);
	while (!file.eof())
	{
		
		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
		nuevo = obj.convert(actual);

	}
	file.close();
}

void CreatePensum::readRegister(string name, estudianteMemo* estu)
{
	fstream file;
	file.open(name, ios::in | ios::binary);

	if (file.fail())
	{
		cout << "Unable to open file, check file\'s path.";
		return;
	}
	materia actual;
	createTreePensum obj;
	file.seekg(sizeof(metaData));
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));

	materiaMemo* nuevo = new materiaMemo();
	nuevo = obj.convert2(actual, estu);
	//obj.addClass(nuevo);
	while (!file.eof())
	{

		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
		nuevo = obj.convert2(actual,estu);

	}
	file.close();
}

void CreatePensum::printPensum(string name)
{
	fstream file;
	file.open(name, ios::in | ios::binary);

	if (file.fail())
	{
		cout << "Unable to open file, check file\'s path.";
		return;
	}
	materia actual;
	createTreePensum obj;
	file.seekg(sizeof(metaData));
	//file.seekg(0);
	file.read(reinterpret_cast<char*>(&actual), sizeof(actual));

	while (!file.eof())
	{
		cout << "\nNombre: " << actual.nombre;
		cout << "\nCodigo: " << actual.codigo;
		cout << "\nUVs: " << actual.UVs;
		cout << "\nAno Periodo: " << actual.anoP;
		cout << "\nPeriodo: " << actual.periodo;
		cout << "\nPadres: ";

		for (int i = 0; i < 4; i++)
		{
			string af = actual.padres[i];
			for (int j = 0; j < af.size(); j++)
			{
				cout << actual.padres[i][j];
			}
			cout << ", ";
		}
		cout << "\nNota: " << actual.nota;
		cout << "\nUVs necesarias: " << actual.UVsRequisito;
		cout << '\n';
		file.read(reinterpret_cast<char*>(&actual), sizeof(actual));
	}
	file.close();
}







