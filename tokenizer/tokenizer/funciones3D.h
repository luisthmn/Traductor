#include <iostream>
#include <cstdlib>
#include <string>
#include <sstream> 
#include <fstream>
#include "Estructuras.h"
#include "Estructuras3D.h"


using namespace std;


//Variables auxiliares
string var;
int Ts =0;
int pT;
bool hayT = false;
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
			//Tenemos que dividir en caracteres cada subdeclaracion
			//Y lo guardamos en un arreglo
			string subdec[200];
			int j = 0;
			int aux = 0;
			var2 = p->subDeclaraciones[i][j];
			while (true){
				if(p->subDeclaraciones[i][j] == ' ') j++;
				subdec[aux] = p->subDeclaraciones[i][j];
				if(p->subDeclaraciones[i][j]==';')break;
				j++;
				aux++;
			}
			////////////////////////////////////////////////
			//Primero realizamos una lectura para extraer las variables auxiliares
			// e imprimirlas
			j = 0;
			pT = Ts+1;
			while(subdec[j]!=";"){
				if( subdec[j] == "*" || subdec[j] == "/" ){
					Ts++;
					if(subdec[j-2]=="*"|| subdec[j] == "/" ) hayT = true;
					if(hayT==false) cout << "t" << Ts << " := " << subdec[j-1] << " " << subdec[j] << " " << subdec[j+1] << endl;
					else cout << "t" << Ts << " := t" << Ts-1 << " " << subdec[j] << " " << subdec[j+1] << endl;
				}
				j++;
			}
			hayT = false;
		/////////////////////////////////////////////////
			//Esta seccion de codigo se encarga de las divisiones de linea
			//adecuadas (Solo dos elementos max por argumento y que se respete la jerarquia de operadores)
			///////////////////////////////////////////////
			aux = 0;
			while(subdec[aux]!=""){
				if( subdec[aux]== "int"  ||  subdec[aux]== "double"  ||  subdec[aux]== "float"){
					aux++;
					cout << subdec[aux];
					//Guardamos la variable a la que le estamos asignando valor
					var = subdec[aux];
					cout << " := ";
					aux+=2;
				}
				else if( subdec[aux] == "="){
					cout << " := ";
					aux++;
				}
				////////////////////////
				//Impresion de consola en codigo 3D
				if(subdec[aux]=="cout"){
					cout << "t" << pT << " := " << subdec[aux+3];
					cout << endl << "out t" << pT;
					pT++;
					aux+=3;
				}
				else if(subdec[aux]=="cin"){
					cout << "t" << pT << " := " << subdec[aux+3];
					cout << endl << "in t" << pT;
					pT++;
					aux+=3;
				}
				//Ningun operador
				else if(subdec[3]==""){
					if(subdec[aux]!="=" && subdec[aux]!=";")cout << subdec[aux];
				}
				//Un solo operador
				else if(subdec[7]=="" && (subdec[0]=="int" || subdec[0]=="double" || subdec[0]=="float")){
					if(subdec[aux]=="+" || subdec[aux]=="-")cout << subdec[aux-1] << " " << subdec[aux];
					else if(subdec[aux]=="*" || subdec[aux]=="/"){
						cout << " t" << pT;
						pT++;
					}
				} 

				//Impresion de las declaraciones usando las variables auxiliares
				 else if(subdec[aux+1]=="=" || (subdec[aux+2]=="" && i==2) ) cout << subdec[aux-1];

				else if(subdec[aux]=="*" || subdec[aux]=="/"){
					if(subdec[aux-2]=="*" || subdec[aux-2]=="/" || subdec[aux-2]=="=")cout << "t" << pT << " ";
					while(subdec[aux+2]=="*" || subdec[aux+2]=="/"){
						aux+=3;
						pT+=3;
					}
				}	
				///////////////////////
				else if(subdec[aux]=="+" || subdec[aux]=="-"){
					if(subdec[aux-2]=="=") cout << subdec[aux-1] << " "; 
					cout << subdec[aux] << " ";
					//Un solo operador
					if(subdec[aux+2]==";") cout << subdec[aux+1];

					while(subdec[aux+2]=="+"|| subdec[aux+2]=="-"){
						cout << subdec[aux+1] << " ";
						cout << endl << subdec[0] << " := "<< subdec[0] << " " <<  subdec[aux+2] << " " << subdec[aux+3]; 
						aux+=2;
					} 
					if(subdec[aux+2]=="+" || subdec[aux+2]=="-"){
						if(subdec[aux-2]!="="){
							cout << subdec[aux+1];
							cout << endl;
							if(subdec[0]!="int" && subdec[0]!="double" && subdec[0]!="float" ){
								cout << subdec[0] << " := ";
								cout << subdec[0] << " ";
							}else{
								cout << subdec[1] << " := ";
								cout << subdec[1] << " ";
							} 
						}
					}
				}
				aux++;
			}
			//-----------------------------------------------------------------------------------------------------------------

			//-------------------------------------------------------------------------------------------------------------------
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

	////////////////////////////////////////////////
		//Primero realizamos una lectura para extraer las variables auxiliares
		// e imprimirlas
		int j = 0;
		pT = Ts+1;
		while(p->simbolos[j]!=";"){
			if( p->simbolos[j] == "*" || p->simbolos[j] == "/" ){
				Ts++;
				if(p->simbolos[j-2]=="*"|| p->simbolos[j] == "/" ) hayT = true;
				if(hayT==false) cout << "t" << Ts << " := " << p->simbolos[j-1] << " " << p->simbolos[j] << " " << p->simbolos[j+1] << endl;
				else cout << "t" << Ts << " := t" << Ts-1 << " " << p->simbolos[j] << " " << p->simbolos[j+1] << endl;
			}
			j++;
		}
		hayT = false;
		/////////////////////////////////////////////////

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
		////////////////////////
		//Impresion de consola en codigo 3D
		if(p->simbolos[i]=="cout"){
			cout << "t" << pT << " := " << p->simbolos[i+3];
			cout << endl << "out t" << pT;
			pT++;
			i+=3;
		}
		else if(p->simbolos[i]=="cin"){
			cout << "t" << pT << " := " << p->simbolos[i+3];
			cout << endl << "in t" << pT;
			pT++;
			i+=3;
		}
		//Ningun operador
		else if(p->lengthDeclaracion<=4){
			if(p->simbolos[i]!="=" && p->simbolos[i]!=";")cout << p->simbolos[i];
		}
		//Un solo operador
		else if(p->lengthDeclaracion <= 8 && (p->simbolos[0]=="int" || p->simbolos[0]=="double" || p->simbolos[0]=="float")){
			if(p->simbolos[i]=="+" || p->simbolos[i]=="-")cout << p->simbolos[i-1] << " " << p->simbolos[i];
			else if(p->simbolos[i]=="*" || p->simbolos[i]=="/"){
				cout << " t" << pT;
				pT++;
			}
		} 

		//Impresion de las declaraciones usando las variables auxiliares
		 else if(p->simbolos[i+1]=="=" || (p->simbolos[i+2]=="" && i==2) ) cout << p->simbolos[i];

		else if(p->simbolos[i]=="*" || p->simbolos[i]=="/"){
			if(p->simbolos[i-2]=="*" || p->simbolos[i-2]=="/" || p->simbolos[i-2]=="=")cout << "t" << pT << " ";
			while(p->simbolos[i+2]=="*" || p->simbolos[i+2]=="/"){
				i+=3;
				pT+=3;
			}
		}	
		///////////////////////
		else if(p->simbolos[i]=="+" || p->simbolos[i]=="-"){
			cout << p->simbolos[i] << " ";
			if(p->simbolos[i+2]=="+" || p->simbolos[i+2]=="-"){
				if(p->simbolos[i-2]!="="){
					cout << p->simbolos[i+1];
					cout << endl;
					if(p->simbolos[0]!="int" && p->simbolos[0]!="double" && p->simbolos[0]!="float" ){
						cout << p->simbolos[0] << " := ";
						cout << p->simbolos[0] << " ";
					}else{
						cout << p->simbolos[1] << " := ";
						cout << p->simbolos[1] << " ";
					} 
				}
			}
		}
		i++;
	}
	cout << endl;
};
//////////////////////////////////////////////////////////////////////////////////////
