#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream> 
#include <fstream>
#include "Estructuras.h"
#include "Estructuras3D.h"


using namespace std;


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
bool signoMasMenos = false;
bool signoPorDiv = false;
string var2;
//////////////////////////////////////////////////////////////////////////////////////
void pintarBloque3D(bloque* p){

	if(p->tipo == "WHILE"){
		cout << "L" << etiquetas << ":\n";
		etiquetas++;
		cout << "if ";
		int i = 0;
		while(p->declaracion[i]!=")"){
			cout << p->declaracion[i];
			var2 = p->declaracion[i];
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
			var2 = p->declaracion[i];
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
			//Esta seccion de codigo se encarga de las divisiones de linea
			//adecuadas (Solo dos elementos max por argumento y que se respete la jerarquia de operadores)
			////////////////////////////////////////////////
			/*if(p->subDeclaraciones[i] == "+" || p->subDeclaraciones[i] == "-") signoMasMenos = true;
			if(p->subDeclaraciones[i] == "*" || p->subDeclaraciones[i] == "/") signoPorDiv = true;
			//Aqui se cubren los dos posibles casos de division de linea
			if(signoMasMenos == true && ((p->subDeclaraciones[i-1] == "*") || (p->subDeclaraciones[i-1] == "/"))){
				cout << endl << var2 << " := " << var2 << " ";
			}
			else if(signoPorDiv == true && ((p->subDeclaraciones[i] == "+") || (p->subDeclaraciones[i] == "-"))){
				cout << endl << var2 << " := " << var2 << " ";
			}*/
			/////////////////////////////////
			cout << p->subDeclaraciones[i];
			if(p->subDeclaraciones[i+1]!="")cout << endl;
			i++;
		}
		/////////////////////////////////////////////////////////////
		cout << endl << "L" << etiquetas << ":\n";
		etiquetas++;
	}
	signoMasMenos = false;
	signoPorDiv = false;
};
//////////////////////////////////////////////////////////////////////////////////////
//Esta funcion recibe una declaracion (fuera de bloque) en c++ y lo pasa a codigo de tres direcciones
//la variable cont es el numero de linea en codigo tres direcciones en el que 
//empezará a pintar
//Variables auxiliares
bool operadorMasMenos = false;
bool operadorPorDiv = false;
string var;
void pintarDeclaracion3D(declaracion* p){

	int i = 0;
	while(p->simbolos[i]!=""){
		if( p->simbolos[i]== "int"  ||  p->simbolos[i]== "double"  ||  p->simbolos[i]== "float"){
			i++;
			cout << p->simbolos[i];
			//Guardamos la variable a la que le estamos asignando valor
			var = p->simbolos[i];
			cout << " := ";
			i+=2;
		}
		else if( p->simbolos[i] == "="){
			cout << " := ";
			i++;
		}
		////////////////////////////////////////////////
		else if( p->simbolos[i] == "+" || p->simbolos[i] == "*" || p->simbolos[i] == "/"|| p->simbolos[i] == "-"){
			if( p->simbolos[i] == "+" ||  p->simbolos[i] == "-") operadorMasMenos = true;
			if( p->simbolos[i] == "*" || p->simbolos[i] == "/") operadorPorDiv = true;
			
			//Aqui se cubren los dos posibles casos de division de linea
			if(operadorMasMenos == true && ((p->simbolos[i-1] == "*") || (p->simbolos[i-1] == "/"))){
				cout << endl << var << " := " << var << " ";
			}
			else if(operadorPorDiv == true && ((p->simbolos[i] == "+") || (p->simbolos[i] == "-"))){
				cout << endl << var << " := " << var << " ";
			}
		}
		cout << p->simbolos[i] << " ";
		i++;
	}
	cout << endl;
	int operador = 1;
	int operadorMasMenos = true;
	int operadorPorDiv = true;
};
//////////////////////////////////////////////////////////////////////////////////////
