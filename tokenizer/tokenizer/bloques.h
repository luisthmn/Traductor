#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

enum{IF, WHILE};

struct bloque {
	string tipo;
	int linInicio;
	int linFin;
	int length;

	bloque *anterior;
	bloque *siguiente;
};

struct simbolo{
	string tipo;
	int lin;

	simbolo *anterior;
};