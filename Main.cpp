
#include <iostream>
#include "createPensum.h"
#include "createTreePensum.h"
using namespace std;

int main()
{
	int option = 0;
	while (option != 4)
	{
		cout << "\n1. Crear Plan de Estudio";
		cout << "\n2. Inscripcion de clases";
		cout << "\n3. Informacion Academica";
		cout << "\n4. Salir";
		cout << "\n\nOpcion: ";
		cin >> option;

		if (option == 1)
		{
			CreatePensum obj;
			obj.addCareer();
			//obj.readPensum("ssssss_plan.dat");
		}
		else if (option == 2)
		{
			createTreePensum obj;
			cout << "===== Inscripcion de Clases =====" << endl;
			cout << "1. Login" << endl;
			cout << "2. Registrar Estudiante" << endl;
			cout << "Ingrese opcion: ";
			int x = 0;
			cin >> x;

			if (x == 1)
			{
				obj.loginEstudiante();
			}
			else if (x == 2)
			{
				obj.crearEstudiante();

			}
		}
		else if (option == 3)
		{
			createTreePensum obj2;
			obj2.informacionAcademica();
		}
		else if (option == 4)
		{

		}
	}
	//obj.extractTextFile(name);

	//system("pause");
}