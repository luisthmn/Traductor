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
	string str = "int ard=25*6+3+4*5*10*8;cout << \"Estupefacto\";while(m<=10){ m++; ard = 3*4+5;} ard =3;if(m==10){ m=m+2+3; m=3*9+8;} int j = 3+4*5; int s = 25; float var=j*j;";
	
	cout << endl << endl << "El codigo c++ a transformar es:\n"<< "int ard = 25*6+3+4*5*10*8;\ncout << \"Estupefacto\";\nwhile(m<=10){\n  m++;\nard = 3*4+5;\n}\nard=3;\nif(m==10){\n  m=m+2+3;\n   m=3*9+8;\n}\nint j = 3+4*5;\nint s = 25;\nfloat var=j*j;" << endl << endl;
	cout << endl << "A continuacion se realizara la lectura de su codigo en c++ para transformarlo a codigo 3 direcciones";
	cout << endl;
	system("pause");
	system("cls");
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

	/////////////
	listaBloques.pintar();
	cout << "En total hay " << listaBloques.Cuantos2() << " bloque(s)\n\n";
	listaDeclaraciones.pintar();
	cout << "En total hay " << listaDeclaraciones.Cuantos() << " Declaracion(es)\n\n";
	/////////////
	int i = 0;
	bloque *p = new bloque;
	declaracion *q = new declaracion;
	p = listaBloques._principio;
	q = listaDeclaraciones._principio;

	//Este ciclo se encarga de ir extrayendo los bloques y declaraciones e ir transformandolos 
	//a codigo de tres direcciones
	//Limpiamos la pantalla antes de pasar a transformar el código
	//(Le avisamos al usuario)
	cout << endl << "Se ha realizado la lectura de su codigo en c++";
	cout << endl << "Ahora se transformara a codigo de tres direcciones\n";
	system("pause");
	system("cls");

	while(true){
		//Revisamos si lo que tenemos que pintar es un bloque
		if(elementos[i] == "while" || elementos[i] =="if"){
			//Sacamos el bloque de la lista y lo pintamos en codigo 3D	
			p = listaBloques.sacar();
			//Guardamos el numero de linea en 3D que nos quedamos
			pintarBloque3D(p);
			//Guardamos que elemento revisaremos despues
			i+= p->lengthDeclaracion + p->lengthInterior + 6;
		}
		//Si no es un bloque entonces lo que tenemos que pintar
		//debe ser una declaracion
		else{
			//Sacamos una declaracion de nuestra lista de 
			//declaraciones y la pintamos
			q = listaDeclaraciones.sacar();
			//Guardamos en que linea de codigo 3D nos quedamos
			pintarDeclaracion3D(q);
			//Guardamos que elemento sigue de revisar despues
			i+= (q->elementoFinalDeclaracion - q->elementoiInicialDeclaracion)+2;
		}
		//Si ya se terminaron todos los bloques y declaraciones entonces
		//terminamos el proceso de transformacion a codigo 3D
		if(listaBloques.Cuantos2()== 0 && listaDeclaraciones.Cuantos()==0) break;
	}
   //////////////////////////////////////////////////////////////////////////////
	//Terminamos el programa
	getch();
	return 0;
}

