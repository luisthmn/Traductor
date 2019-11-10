#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

/////////////////////////////////////
struct bloque{                            
	string tipo;
	int elementoiInicialDeclaracion;
	int elementoFinalDeclaracion;
	int elementoiInicialinterior;
	int elementoFinalinterior;
	int lengthDeclaracion;
	int lengthInterior;
	int linInicioInterior;
	int linFinInterior;
	string declaracion[100];
    bloque *siguiente;
};
/////////////////////////////////////
struct declaracion{                            
	string simbolos[200];
	int elementoiInicialDeclaracion;
	int elementoFinalDeclaracion;
	int lengthDeclaracion;
    declaracion *siguiente;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class colaBloque{
    bloque *_principio, *_final;
    int cuantos2;

    public:
        colaBloque();
        ~colaBloque();
        void agregar(string a, int elementoInicalDeclaracion, int elementoFinalDeclaracion, int elementoInicialInterior, int elementoFinalInterior, string codigo[]);
        string sacar();
        void pintar();
        int Cuantos2();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class colaDeclaracion{
    declaracion *_principio, *_final;
    int cuantos;

    public:
        colaDeclaracion();
        ~colaDeclaracion();
        void agregar(string codigo[], int elementoInicalDeclaracion, int elementoFinalDeclaracion);
        string sacar();
        void pintar();
        int Cuantos();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      COLAS BLOQUES

colaBloque::colaBloque(){
    _principio = NULL;
    _final = NULL;
    cuantos2 = 0;
}
//////////////////////////////////////
void colaBloque::agregar(string a, int elementoInicialDeclaracion, int elementoFinalDeclaracion, int elementoInicialInterior,int elementoFinalInterior, string codigo[]){
    bloque *p;
    p = new bloque;
    p->tipo = a;
	if(p->tipo == "while") p->tipo = "WHILE";
	if(p->tipo == "if") p->tipo = "IF";
	p->elementoiInicialDeclaracion = elementoInicialDeclaracion;
	p->elementoFinalDeclaracion = elementoFinalDeclaracion;
	p->lengthDeclaracion = elementoFinalDeclaracion - elementoInicialDeclaracion;
	p->elementoiInicialinterior = elementoInicialInterior;
	p->elementoFinalinterior = elementoFinalInterior;
	p->lengthInterior = elementoFinalInterior - elementoInicialInterior;
	
	int i = 0, aux = elementoInicialDeclaracion;
	while(i<=p->lengthDeclaracion){
		p->declaracion[i] = codigo[aux];
		i++;
		aux++;
	}

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
string colaBloque::sacar(){
    bloque *p;
    string valor;

    if(_principio != NULL){
        p = _principio;
        _principio = p->siguiente;
        valor = p->tipo;
        delete p;
        cuantos2--;
    }
    else{
        _final = NULL;
        return "VACIO";
    }
    return valor;
}
///////////////////////////////////
colaBloque::~colaBloque(){
    bloque *p;

    while(_principio){
        p = _principio;
        _principio = p -> siguiente;
        delete p;
    }
    return;
}
///////////////////////////////
int colaBloque::Cuantos2(){
    return(cuantos2);
}
/////////////////////////////////////////////
void colaBloque::pintar(){
    bloque *p;
    p = _principio;

	cout << endl << endl << "Esta es la lista de bloque encontrados"<< endl;
	while(p){
        cout << "\n" << "tipoBloque: " << p -> tipo;

		//Pintamos la declaracion del bloque
		int i = 0;
		cout << "\n" << "Declaracion Bloque:(";
		while(i<= p->lengthDeclaracion){
			cout << p->declaracion[i];
			i++;
		}
		cout << ")";

		cout << "\n" << "numero de elemento inicial declaracion: " << p ->elementoiInicialDeclaracion;
		cout << "\n" << "numero de elemento final declaracion: " << p ->elementoFinalDeclaracion;
		cout << "\n" << "Cantidad de elementos en la declaracion del bloque: " << p ->lengthDeclaracion;
		cout << "\n" << "numero de elmento inicial en el interior: " << p ->elementoiInicialinterior;
		cout << "\n" << "numereo de elemento final en el interior: " << p->elementoFinalinterior;
		cout << "\n" << "Cantidad de elementos en el interior del bloque: " << p ->lengthInterior;
		cout << endl << endl;
        p = p -> siguiente;
    }
}
////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//      COLAS DESCLARACION

colaDeclaracion::colaDeclaracion(){
    _principio = NULL;
    _final = NULL;
    cuantos = 0;
}
//////////////////////////////////////
void colaDeclaracion::agregar(string codigo[], int elementoInicialDeclaracion, int elementoFinalDeclaracion){
    declaracion *p;
    p = new declaracion;
	
	p->elementoiInicialDeclaracion = elementoInicialDeclaracion;
	p->elementoFinalDeclaracion = elementoFinalDeclaracion;
	p->lengthDeclaracion = elementoFinalDeclaracion - elementoInicialDeclaracion;
	
	int i = 0, aux =elementoInicialDeclaracion;
	while(i<=p->lengthDeclaracion){
		p->simbolos[i] = codigo[aux];
		i++;
		aux++;
	}

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
    cuantos++;
}
/////////////////////////////////////
string colaDeclaracion::sacar(){
    declaracion *p;
    string valor;

    if(_principio != NULL){
        p = _principio;
        _principio = p->siguiente;
        delete p;
        cuantos--;
    }
    else{
        _final = NULL;
        return "VACIO";
    }
    return "Elemento eliminado";
}
///////////////////////////////////
colaDeclaracion::~colaDeclaracion(){
    declaracion *p;

    while(_principio){
        p = _principio;
        _principio = p -> siguiente;
        delete p;
    }
    return;
}
///////////////////////////////
int colaDeclaracion::Cuantos(){
    return(cuantos);
}
/////////////////////////////////////////////
void colaDeclaracion::pintar(){
    declaracion *p;
    p = _principio;

	cout << endl << endl << "Esta es la lista de declaraciones encontradas (Que estan fuera de los bloques)"<< endl << endl;
	while(p){

		int j = 0;
		//Pintamos la declaracion
		int i = 0;
		cout << "\n" << "Declaracion #: " << "(";
		while(i<= p->lengthDeclaracion){
			cout << p->simbolos[i];
			i++;
		}
		cout << ")";

		cout << "\n" << "numero de elemento inicial declaracion: " << p ->elementoiInicialDeclaracion;
		cout << "\n" << "numero de elemento final declaracion: " << p ->elementoFinalDeclaracion;
		cout << "\n" << "Cantidad de elementos en la declaracion del bloque: " << p ->lengthDeclaracion;
		cout << endl << endl;
        p = p -> siguiente;
    }
}
////////////////////////////////////////////