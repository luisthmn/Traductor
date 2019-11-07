#pragma once
#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

enum{IF, WHILE};

struct bloque {
	string tipo;

	int linInicio;
	int linFinal;
	int length;

	bloque *anterior;
	bloque *siguiente;
};
struct simbolo{

	string tipo;
	bloque *anterior;
};