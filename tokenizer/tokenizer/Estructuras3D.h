#include <iostream>
#include <cstdlib>
#include <string>


using namespace std;

//Esta estructura es para ir almacenando todas las variables
//encontradas en el codigo c++ y poder referirlas mas adelante
//cuando estemos escribiendo el codigo de tres direcciones
////////////////////////////////////
struct variables{                           //Lista doblemente ligadas
	string nombrec;
	string linea3D;

    variables *siguiente;
};
///////////////////////////////////
//Esta clase es la que contiene las estructuras de las variables
class listaVar{
    variables *_principio, *_final;
    int cuantos2;

    public:
        listaVar();
        ~listaVar();
		string buscar(string a);
        void agregar(string a, int cont);
        void pintar();
        int Cuantos2();
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
listaVar::listaVar(){
    _principio = NULL;
    _final = NULL;
    cuantos2 = 0;
}
//Esta funcion busca una variable en la clase y regresa su equivalente en el codigo 
//de tres direcciones, lo cual quiere decir que regresa en que linea del codigo de tres direcciones
//fue declarada
//////////////////////////////////////
string listaVar::buscar(string a){
	variables *p;
	p = _principio;
	while(p){
		//cout << endl << endl << "Comparando " << a << " con el elemento " << p->nombrec << endl;
		if(p->nombrec == a){
			return p->linea3D;
		}
		else{
			p = p->siguiente;
		}
	}
	return "NADA";
}
///////////////////////////////////////
//Funcion para agregar una variable nueva a la clase
void listaVar::agregar(string a, int cont){
    variables *p;
    p = new variables;
    p->nombrec = a;
	p->linea3D = cont;

    if(_principio != NULL){
        p->siguiente = NULL;
        _final->siguiente = p;
        _final = p;
    }
    else{
        p->siguiente = NULL;
        _principio = p;
        _final = p;
    }
    cuantos2++;
}
/////////////////////////////////////
listaVar::~listaVar(){
    variables *p;

    while(_principio){
        p = _principio;
        _principio = p -> siguiente;
        delete p;
    }
    return;
}
///////////////////////////////
int listaVar::Cuantos2(){
    return(cuantos2);
}
/////////////////////////////////////////////
void listaVar::pintar(){
    variables *p;
    p = _principio;
    while(p){
        cout << "\n " << p -> nombrec;
        p = p -> siguiente;
    }
	cout << endl << endl << "En total hay " << cuantos2 << " variables" << endl;
}
/////////////////////////////////////////////