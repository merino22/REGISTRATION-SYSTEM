#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H
#include <string>
#include <string.h>

using namespace std;

struct estudiante
{
	int numCuenta;
	char nombre[100];
	char nombrePlan[100];
	double indice;
	int clasesAprobadas;

	estudiante()
	{
		numCuenta = 0;
		nombre[99] = { 0 };
		nombrePlan[99] = { 0 };
		indice = 0;
		clasesAprobadas = 0;
	}

	estudiante(int _numCuenta, char _nombre[], char _nombrePlan[], double _indice, int _clasesAprobadas)
	{
		numCuenta = _numCuenta;
		setNombre(nombre, _nombre);
		setNombrePlan(nombrePlan, _nombrePlan);
		indice = _indice;
		clasesAprobadas = _clasesAprobadas;
	}

	void setNombre(char nombrex[], char _nombrex[])
	{
		string as = _nombrex;

		for (int i = 0; i < as.size(); i++)
		{
			nombrex[i] = _nombrex[i];
		}
	}

	void setNombrePlan(char nombrex[], char _nombrex[])
	{
		string as = _nombrex;

		for (int i = 0; i < as.size(); i++)
		{
			nombrex[i] = _nombrex[i];
		}
	}
};

struct estudianteMemo
{
	int numCuenta;
	char* nombre;
	char* nombrePlan;
	double indice;
	int clasesAprobadas;

	estudianteMemo()
	{
		numCuenta = 0;
		nombre = 0;
		nombrePlan = 0;
		indice = 0;
		clasesAprobadas = 0;
	}
};
#endif