#pragma once

#include <cstdlib>
#include <cstdio>
#include <string>

using namespace std;

enum{IF, WHILE};

struct bloque {
	string tipo;

<<<<<<< HEAD
	int linInicio;
	int linFinal;
	int length;

	bloque *anterior;
	bloque *siguiente;
};
struct simbolo{

	string tipo;
	bloque *anterior;
=======
>>>>>>> 395f0838c7ef5bb043017c9b0d7119d3ac28d35e
};