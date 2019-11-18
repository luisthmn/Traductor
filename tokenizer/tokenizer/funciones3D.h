#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream> 
#include "Estructuras.h"
#include "Estructuras3D.h"


using namespace std;

class listaVar listaVar;

//Funcion auxiliar que revisa que una cadena contenga solo digitos
//////////////////////////////////////////////////////////////////////////////////////
bool is_digits(const std::string &str)
{
    return std::all_of(str.begin(), str.end(), ::isdigit); // C++11
}
//////////////////////////////////////////////////////////////////////////////////////

//Esta funcion recibe un bloque en c++ y lo pasa a codigo de tres direcciones
//la variable cont es el numero de linea en codigo tres direcciones en el que 
//empezar� a pintar
int pintarBloque3D(bloque* p, int cont){
	cout << "\nt" << cont << " := "; 

	cont++;
	return cont;
};
//////////////////////////////////////////////////////////////////////////////////////
//Esta funcion recibe una declaracion (fuera de bloque) en c++ y lo pasa a codigo de tres direcciones
//la variable cont es el numero de linea en codigo tres direcciones en el que 
//empezar� a pintar
int pintarDeclaracion3D(declaracion* p, int cont){
	cout << "\nt" << cont << " := ";
	
	int i = 0;
	while(p->simbolos[i]!=""){
		//Si se encuentra una declaracion de variable entonces tenemos que guardarla
		//para poder referirla si se utiliza mas adelante
		if( p->simbolos[i]== "int"  ||  p->simbolos[i]== "double"  ||  p->simbolos[i]== "float"){
			i++;
			//En este punto p->simbolos[i] tiene el nombre de la variable declarada asi que la guardamos
			//junto con el numero de linea en el que est� ahora en el codigo 3D
			listaVar.agregar(p->simbolos[i], cont);
			while(p->simbolos[i]!="="){
				i++;
			}
			i++;
		}
		//Si no encontramos una declaracion de variable entonces revisamos si
		//el contenido de la declaracion utiliza variables que ya han sido declaradas
		//anteriormente (Y que guardamos)
		if(!is_digits(p->simbolos[i]) && p->simbolos[i]!="+" && p->simbolos[i]!="-" && p->simbolos[i]!="*"&& p->simbolos[i]!="/"){
		//	cout << endl << endl << "Buscando "<< p->simbolos[i] << " en la clase de variables" << endl;
			//Hacemos un poco de magia aqu� para transformar el numero de linea en codigo 3 direcciones
			//correspondiente a la variable que usamos
			stringstream ss;
			ss << listaVar.buscar(p->simbolos[i]);
			p->simbolos[i] = "t" + ss.str();
		}
		cout << p->simbolos[i];
		i++;
	}
	cout << ";";
	cont++;
	return cont;
};
//////////////////////////////////////////////////////////////////////////////////////
