#ifndef MATERIA_H
#define MATERIA_H

#include <string>
#include <string.h>

using namespace std;

struct materia
{
	char codigo[10];
	char nombre[100];
	int UVs;
	int anoP;
	int periodo;
	char padres[4][10] = { 0 };
	double nota;
	int UVsRequisito;
	int cantHijos;

	materia()
	{
		codigo[0] = { 0 };
		nombre[0] = { 0 };
		UVs = 0;
		anoP = 0;
		periodo = 0;
		nota = 0;
		UVsRequisito = 0;
		cantHijos = 0;
	}

	materia(char _codigo[], char _nombre[], int _UVs, int _anoP, int _periodo, char _padre[4][10])
	{
		setCodigo(codigo, _codigo);
		setNombre(nombre, _nombre);
		UVs = 0;
		anoP = 0;
		periodo = 0;
		setPadre(padres, _padre);
		nota = 0;
		UVsRequisito = 0;
		cantHijos = 0;
	}

	void setCodigo(char code[10], char _code[10])
	{
		string as = _code;
		for (int i = 0; i < as.size(); i++)
		{
			code[i] = _code[i];
		}
	}

	void setNombre(char name[100], char _name[100])
	{
		string as = _name;
		for (int i = 0; i < as.size(); i++)
		{
			name[i] = _name[i];
		}
	}

	void setPadre(char padre[4][10], char _padre[4][10])
	{

		for (int i = 0; i < 4; i++)
		{
			string as = _padre[i];
			for (int j = 0; j < as.size(); j++)
			{
				padre[i][j] = _padre[i][j];
			}
		}
	}
	
	void setHijos(char hijos[4][10], char _hijos[4][10])
	{
		for (int i = 0; i < 4; i++)
		{
			string as = _hijos[i];
			for (int j = 0; j < as.size(); j++)
			{
				hijos[i][j] = _hijos[i][j];
			}
		}
	}
};

struct materiaMemo
{
	char* codigo;
	char* nombre;
	int UVs;
	int anoP;
	int periodo;
	materiaMemo** hijos;
	char** padres;
	bool pass;
	int UVsRequisito;
	int cantHijos, cantPadres;

	materiaMemo() : codigo(0), nombre(0), UVs(0), anoP(0), periodo(0), hijos(0), padres(0), UVsRequisito(0), cantHijos(0), cantPadres(0), pass(0) {}
	materiaMemo(char _codigo[], char _nombre[], int _UVs, int _anoP, int _periodo, char _padres[4][10], int _nota, int _UVsRequisito)
	{
		codigo = _codigo;
		nombre = _nombre;
		UVs = _UVs;
		anoP = _anoP;
		hijos = 0;
		setPadres(padres, _padres);
		pass = setPass(_nota);
		UVsRequisito = _UVsRequisito;
		cantHijos = 0;
		cantPadres = 0;
	}

	void setCodigo(char code[10], char _code[10])
	{
		for (int i = 0; i < 10; i++)
		{
			code[i] = _code[i];
		}
	}

	void setPadres(char** padres, char _padres[4][10])
	{
		for (int i = 0; i < 4; i++)
		{
			string as = _padres[i];
			if (as != "")
			{
				for (int j = 0; j < as.size(); j++)
				{
					padres[i][j] = _padres[i][j];
				}
			}
		}
	}

	void setpadres(char* padre) {
		char** tmp = new char* [cantPadres + 1];
		for (size_t i = 0; i < cantPadres; i++)
		{
			if (padres[i] != "")
			{
				tmp[i] = padres[i];
			}
		}
		tmp[cantPadres] = new char[strlen(padre)];
		strcpy_s(tmp[cantPadres], strlen(padre) + 1, padre);
		if (padres != 0)
		{
			delete padres;
		}
		cantPadres++;
		padres = tmp;
	};

	void setNombre(char name[100], char _name[100])
	{
		for (int i = 0; i < 100; i++)
		{
			name[i] = _name[i];
		}
	}

	bool setPass(int _nota)
	{
		if (_nota > 60)
		{
			return true;
		}
		return false;
	}

};

struct materiaMemoImp
{

};

struct metaData
{
	char codigoPlan[10];
	char nombrePlan[100];
	int totalClases;
	int totalUVs;
	int cantBloques;

	metaData()
	{
		codigoPlan[9] = { 0 };
		nombrePlan[99] = { 0 };
		totalClases = 0;
		totalUVs = 0;
		cantBloques = 0;
	}

	metaData(char _codigo[], char _nombre[], int _totalClases, int _totalUVs, int _cantBloques)
	{
		strcpy_s(codigoPlan, _codigo);
		strcpy_s(nombrePlan, _nombre);
		totalClases = _totalClases;
		totalUVs = _totalUVs;
		cantBloques = _cantBloques;
	}
};

struct code
{
	int codex;

	code()
	{
		codex = 0;
	}
};
struct notas
{
	char nombreClase[10] = { 0 };
	double notaClase;
	int UVs;

	notas()
	{
		notaClase = 0;
		UVs = 0;
	}
};

#endif