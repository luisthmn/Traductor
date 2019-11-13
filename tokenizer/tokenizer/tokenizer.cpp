// tokenizer.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include <boost/tokenizer.hpp>
#include <string>
#include <conio.h>
#include <cstdlib>
#include <sstream> 
#include <iostream>
#include "funciones3D.h"

using namespace std;

int main()
{
	//lista de bloques del codigo (Los comandos IF y WHILE) y de declaraciones
	colaBloque listaBloques;
	colaDeclaracion listaDeclaraciones;

	//Variable para sacar la cantidad de elementos en una declaracion fuera de un bloque
	int auxDeclaracion = 0;
	//Variable para sacar la cantidad de elementos que abarca la declaracion de un bloque
	int auxDeclaracionBloque = 0;
	//Variable para llevar control del elemento en el que estamos
	int numElemento = 0;
	//Variable para llevar control del elemento en el que inicio una declaracion
	int lineaInicioDeclaracion = 0;
	//Variable para llevar control del elemento en el que inicio la declaracion de un bloque
	int lineaInicioDeclaracionBloque = 0;
	//Variable para saber si estamos dentro de la declaracion de un bloque
	bool dentroDeclaracionBloque = false;
	//Variable para saber si estamos en el interior de un bloque
	bool dentroInteriorBloque = false;
	//Variable para saber si estamos en el interior de una declaracion
	bool dentroDeclaracion = false;
	////Variable para sacar la cantidad de elementos que abarca el interior de un bloque
	int auxInteriorBloque = 0;
	//Arreglo bloques/simbolos
	string elementos[1000];
	int cantidadElementos = 0;

	//Datos auxiliares para agregar Bloques
	//////////////////////////////////////
	string tipoBloqueAux;
	int elementoInicialDeclaracionAux;
	int elementoFinalDeclaracionAux;
	int elementoInicialInteriorAux;
	int elementoFinalInteriorAux;
	//////////////////////////////////////

	//Inicio del Tokenizador,
	/////////////////////////////////////////////////////////////////////////////
	//Primero insertamos el codigo que evaluaremos
	std::string str = "while(m<=10){ cout << m; m++;} if(m==10){ m=m+2;} int j = 3+4; int s = 25; s=m*m;";
	
	cout << endl << endl << "El codigo c++ a transformar es:\n"<< "while(m<=10){\n  cout << m; m++;\n}\nif(m==10){\n  m=m+2;\n}\nint j = 3+4;\nint s = 25;\ns=m*m;" << endl << endl;
	cout << endl << "El tokenizador separo los simbolos de la siguiente forma:\n";

	/////////////////////////////////////////////////////////////////////////////////////
	//Esto es magia que utiliza librerias que no entiendo, no entenderé ni deseo entender
	//Pero separa cada simbolo/bloque encontrado en el codigo
    typedef boost::tokenizer<boost::char_separator<char> > 
        tokenizer;
    boost::char_separator<char> sep(" ","(=;)++<*");
    tokenizer tokens(str, sep);

	/////////////////////////////////////////////////////////////////////////////////////

	//Ciclo que se repetira por cada bloque/simbolo en el codigo insertado
    for (tokenizer::iterator tok_iter = tokens.begin();
         tok_iter != tokens.end(); ++tok_iter){
		 
		 //Llevamos cuenta de la cantidad de elementos en el codigo
		 cantidadElementos++;
		 //Anotamos el bloque/simbolo encontrado en consola junto con el numero de elemento que es
		 cout << "#" << numElemento << ":" << *tok_iter;

		 ///////////////////////////////////////////////////////////////////////////////////////////////////////
		 //Si no estamos dentro de un bloque y no estamos comenzando uno entonces estamos en una declaracion
		 if(!dentroDeclaracionBloque && !dentroInteriorBloque && *tok_iter!="while" && *tok_iter!="if"){
			 //Si aun no hemos comenzado la declaracion entonces declaramos su inicio
			 if(dentroDeclaracion == false) lineaInicioDeclaracion = numElemento;
			 dentroDeclaracion = true;
			 auxDeclaracion++;
		 }
		 //Revisamos si llegamos al final de la declaracion
		 if(*tok_iter == ";"&& !dentroDeclaracionBloque && !dentroInteriorBloque){
			 //Si finalizo la declaracion entonces declaramos que ya no estamos en una
			 dentroDeclaracion = false;
			 //Procedemos a agregar la declaracion
			 listaDeclaraciones.agregar(elementos, lineaInicioDeclaracion, numElemento-1);
			 lineaInicioDeclaracion = 0;
		 }
		 ///////////////////////////////////////////////////////////////////////////////////////////////////////
		

		 ////////////////////////////////////////////////////////////////////////////////////////////////
		 //Si estamos dentro de la declaracion de un bloque incrementamos su cantidad de elementos
		 if(dentroDeclaracionBloque){
			 auxDeclaracionBloque++;
			 //Si la declaracion del bloque se termina en este elmento entonces guardamos su declaracion
			 // y declaramos que ya no estamos en una declaracion de bloque
			 if(*tok_iter == ")"){
					elementoInicialDeclaracionAux = lineaInicioDeclaracionBloque+2;
					elementoFinalDeclaracionAux = numElemento-1;
					elementoInicialInteriorAux = numElemento+2;
					dentroDeclaracionBloque = false;
					dentroInteriorBloque = true;
					auxDeclaracionBloque = 0;
			 }
		 }

		 ////////////////////////////////////////////////////////////////////////////////////////////////

		 //Si estabamos dentro del interior de un bloque
		 if(dentroInteriorBloque){
			 //Incrementamos la cantidad de elementos en su interior
			 auxInteriorBloque++;
			 //Revisamos si este es el final del interior del bloque y si lo es
			 //declaramos que ya no estamos en el bloque
			 if(*tok_iter == "}"){
				dentroInteriorBloque = false;
				//Una vez terminado el bloque lo agregamos a la lista de bloques
				listaBloques.agregar(tipoBloqueAux, elementoInicialDeclaracionAux, elementoFinalDeclaracionAux, elementoInicialInteriorAux, numElemento-1, elementos);
				elementoInicialDeclaracionAux = 0;
				elementoFinalDeclaracionAux = 0;
				elementoInicialInteriorAux = 0;
				elementoFinalInteriorAux = 0;
			 }
		 }

		 ///////////////////////////////////////////////////////////////////////////////////////////////

		 //Si encontramos una llave quiere decir que comienza el interior de un bloque
		 if(*tok_iter == "{"){
			 dentroInteriorBloque = true;
			 //Comenzamos a contar la cantidad de elementos que contiene el interior del bloque
			 auxInteriorBloque = 0;
		 }

		 ////////////////////////////////////////////////////////////////////////////////////////////////

		 //Si encontramos el inicio de un bloque, entonces marcamos que estamos apunto de entrar en su declaracion
		 //y comenzamos a contar las linea que contiene su declaracion
		 if(*tok_iter == "while" || *tok_iter == "if"){
			 //Guardamos que tipo de bloque es para cuando lo tengamos que guardar
			 tipoBloqueAux = *tok_iter;
			 //Guardamos en que elemento inicio la declaracion bloque
			 lineaInicioDeclaracionBloque = numElemento;
			 //Iniciamos el conteo de elementos dentro del bloque
			 auxDeclaracionBloque = 0;
			 //Declaramos que a partir de ahora estamos dentro del bloque
			 dentroDeclaracionBloque = true;
		 }

		 ////////////////////////////////////////////////////////////////////////////////////////////////

		 //Guardamos en la lista el bloque/elemento encontrado
		 elementos[numElemento] = *tok_iter;
		 //Pasamos al siguiente elemento
		 numElemento++;
		 cout << endl;
	}
	//Fin de lectura del codigo
	//Ahora procedemos a transformar el codigo a codigo de 3 direcciones
	int i = 0;
	bloque *p = new bloque;
	declaracion *q = new declaracion;
	p = listaBloques._principio;
	q = listaDeclaraciones._principio;

	while(i<=cantidadElementos){
		if(elementos[i] == "while" || elementos[i] =="if"){
				p = listaBloques.sacar();
				cout << endl << "Imprimi el bloque en modo 3D " << endl;
				cout << endl << "saque el bloque " << endl;
				i+= (p->lengthDeclaracion+2) + (p->lengthInterior+2); 
		}
		else{
			   p = listaDeclaraciones.sacar();
		}
		
		
		//cout << Datos->tipo << endl;
		//cout << Datos->finalCondicional << endl;
		break;
	}
   //////////////////////////////////////////////////////////////////////////////
	listaBloques.pintar();
	cout << "En total hay " << listaBloques.Cuantos2() << " bloque(s)\n\n";
	listaDeclaraciones.pintar();
	cout << "En total hay " << listaDeclaraciones.Cuantos() << " Declaracion(es)\n\n";
	//Terminamos el programa
	getch();
	return 0;
}

