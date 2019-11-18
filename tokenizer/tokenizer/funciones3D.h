#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream> 
#include <fstream>
#include "Estructuras.h"
#include "Estructuras3D.h"


using namespace std;

class listaVar listaVar;

int etiquetas = 1;
int cont = 0;
//Funcion auxiliar que revisa que una cadena contenga solo digitos
//////////////////////////////////////////////////////////////////////////////////////
bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}
//////////////////////////////////////////////////////////////////////////////////////

//Esta funcion recibe un bloque en c++ y lo pasa a codigo de tres direcciones
//la variable cont es el numero de linea en codigo tres direcciones en el que 
//empezará a pintar
//////////////////////////////////////////////////////////////////////////////////////
void pintarBloque3D(bloque* p){

	if(p->tipo == "WHILE"){
		cout << "L" << etiquetas << ":\n";
		etiquetas++;
		cout << "if ";
		int i = 0;
		while(p->declaracion[i]!=")"){
			cout << p->declaracion[i];
			i++;
		}
		cout << " goto L" << etiquetas;
		cout << "\n" << "goto L" << etiquetas+1<< "\n";
		cout << "L" << etiquetas<< ":\n";
		etiquetas++;
		////////////////////////////////////////////////////////////////
		//En esta area imprimimos todo lo que esté dentro del while
		i = 0;
		while(p->subDeclaraciones[i] !=""){
			cout << p->subDeclaraciones[i];
			if(p->subDeclaraciones[i+1]!="")cout << endl;
			i++;
		}
		/////////////////////////////////////////////////////////////
		cout << endl << "goto L" << etiquetas-2;
		cout << endl << "L" << etiquetas << ":\n";
		etiquetas++;
	}

	if(p->tipo == "IF"){
		cout << "if ";
		int i = 0;
		while(p->declaracion[i]!=")"){
			cout << p->declaracion[i];
			i++;
		}
		cout << " goto L" << etiquetas;
		cout << "\n" << "goto L" << etiquetas+1<< "\n";
		cout << "L" << etiquetas<< ":\n";
		etiquetas++;

		////////////////////////////////////////////////////////////////
		//En esta area imprimimos todo lo que esté dentro del if
		i = 0;
		while(p->subDeclaraciones[i] !=""){
			cout << p->subDeclaraciones[i];
			if(p->subDeclaraciones[i+1]!="")cout << endl;
			i++;
		}
		/////////////////////////////////////////////////////////////
		cout << endl << "L" << etiquetas << ":\n";
		etiquetas++;
	}
};
//////////////////////////////////////////////////////////////////////////////////////
//Esta funcion recibe una declaracion (fuera de bloque) en c++ y lo pasa a codigo de tres direcciones
//la variable cont es el numero de linea en codigo tres direcciones en el que 
//empezará a pintar
void pintarDeclaracion3D(declaracion* p){

	int i = 0;
	while(p->simbolos[i]!=""){
		if( p->simbolos[i]== "int"  ||  p->simbolos[i]== "double"  ||  p->simbolos[i]== "float"){
			i++;
			listaVar.agregar(p->simbolos[i], cont);
			cout << p->simbolos[i];
			cout << " := ";
			i++;
		}
		cout << p->simbolos[i];
		i++;
	}
	cout << endl;
};
//////////////////////////////////////////////////////////////////////////////////////
