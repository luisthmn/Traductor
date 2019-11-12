#include <iostream>
#include <cstdlib>
#include <string>
#include "Estructuras.h"

struct datos{
	string tipo;
	int inicioInterior;
	int finalInterior;
	int inicioCondicional;
	int finalCondicional;
};
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////
datos *buscarBloque(int i, colaBloque Bloques){

	datos *Datos = new datos;
	bloque *p = new bloque;
	p = Bloques._principio;

	while(p){
		if(p->elementoiInicialDeclaracion == i+2){
			Datos->tipo = p->tipo;
			Datos->finalCondicional = p->elementoFinalDeclaracion;
			Datos->inicioCondicional = p->elementoiInicialDeclaracion;
			Datos->finalInterior = p->elementoFinalinterior;
			Datos->inicioInterior = p->elementoiInicialinterior;

			return Datos;

		}else{
			p= p->siguiente;
		}
	};
	return NULL;
};
//////////////////////////////////////////////////////////////////////////////////////
int buscarElemento(int i){
	return 1;
};
//////////////////////////////////////////////////////////////////////////////////////
/*datos obtenerDatos(int i){
	return NULL;
};*/
//////////////////////////////////////////////////////////////////////////////////////
void pintarBloque3D(colaBloque Bloque){

};
//////////////////////////////////////////////////////////////////////////////////////
void pintarDeclaracion3D(colaDeclaracion Declaracion){

};
//////////////////////////////////////////////////////////////////////////////////////