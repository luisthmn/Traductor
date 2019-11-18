#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

/////////////////////////////////////
struct declaracion{                            
	string simbolos[200];
	int elementoiInicialDeclaracion;
	int elementoFinalDeclaracion;
	int lengthDeclaracion;
    declaracion *siguiente;
};
//////////////////////////////////////
class colaDeclaracion{
    
    int cuantos;

    public:
		declaracion *_principio, *_final;
        colaDeclaracion();
        ~colaDeclaracion();
        void agregar(string codigo[], int elementoInicalDeclaracion, int elementoFinalDeclaracion);
        declaracion* sacar();
        void pintar();
        int Cuantos();
};
/////////////////////////////////////////////////////////////////////////
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
	string subDeclaraciones[40];
	string declaracion[100];
    bloque *siguiente;
};
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class colaBloque{

    int cuantos2;

    public:
		bloque *_principio, *_final;
        colaBloque();
        ~colaBloque();
        void agregar(string a, int elementoInicalDeclaracion, int elementoFinalDeclaracion, int elementoInicialInterior, int elementoFinalInterior, string codigo[]);
        bloque* sacar();
        void pintar();
        int Cuantos2();
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





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
	p->lengthDeclaracion = elementoFinalDeclaracion - elementoInicialDeclaracion + 1;
	p->elementoiInicialinterior = elementoInicialInterior;
	p->elementoFinalinterior = elementoFinalInterior;
	p->lengthInterior = elementoFinalInterior - elementoInicialInterior;
	

	//Esta parte es para guardar las subdeclaraciones (declaraciones adentro del bloque)
	int aux2 = 0;
	int i = elementoInicialInterior;
	while(i<=elementoFinalInterior){
			if(codigo[i]!= ";"){
				if(codigo[i] == "=") p->subDeclaraciones[aux2]+= " := ";
				else p->subDeclaraciones[aux2]+= codigo[i];
			}
			if(codigo[i]== ";")aux2++;
			
			i++;
	}
	p->subDeclaraciones[aux2] = "";

	i = 0;
	int aux = elementoInicialDeclaracion;
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
bloque* colaBloque::sacar(){
    bloque *p;

    if(_principio != NULL){
		p = _principio;
		_principio = p->siguiente;
		cuantos2--;
    }
    else{
        _final = NULL;
        return NULL;
    }
	return p;
	delete p;
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

		cout << "\n" << "Inicio Declaracion: " << p ->elementoiInicialDeclaracion;
		cout << "\n" << "Fin Declaracion: " << p ->elementoFinalDeclaracion;
		cout << "\n" << "Tamano declaracion Bloque: " << p ->lengthDeclaracion;
		cout << "\n" << "Inicio Interior: " << p ->elementoiInicialinterior;
		cout << "\n" << "Final Interior: " << p->elementoFinalinterior;
		cout << "\n" << "Tamano Interior: " << p ->lengthInterior;
		cout << "\n" << "Declaraciones en el interior del Bloque:";
		//Pintamos la subdeclaraciones del bloque
		i = 0;
		while(p->subDeclaraciones[i]!=""){
			cout << "\n" << "(";
			cout << p->subDeclaraciones[i];
			cout << ")";
			i++;
		}

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
	p->lengthDeclaracion = elementoFinalDeclaracion - elementoInicialDeclaracion + 1;
	
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
declaracion* colaDeclaracion::sacar(){
    declaracion *p;

    if(_principio != NULL){
        p = _principio;
        _principio = p->siguiente;
        cuantos--;
    }
    else{
        _final = NULL;
        return NULL;
    }
	return p;
	delete p;
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
	int j = 1;
	while(p){

		
		//Pintamos la declaracion
		int i = 0;
		cout << "\n" << "Declaracion #" << j << ": (";
		while(i<= p->lengthDeclaracion){
			cout << p->simbolos[i];
			i++;
		}
		cout << ")";

		cout << "\n" << "Inicio Declaracion: " << p ->elementoiInicialDeclaracion;
		cout << "\n" << "Fin Declaracion: " << p ->elementoFinalDeclaracion;
		cout << "\n" << "Tamano Declaracion: " << p ->lengthDeclaracion;
		cout << endl << endl;
        p = p -> siguiente;
		j++;
    }
}
////////////////////////////////////////////