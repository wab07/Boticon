#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <string>

using namespace std;

struct Medicina{
	int idMedicina;
	string tipoMedicina
	string nombreMedicina
	int cantMedicina
};

typedef struct Medicina *TpLista;
TpLista añadirMedicina(){
    	TpLista nuevo=NULL;
    	nuevo= new(struct Medicina);
    	cout<<"Ingresar idMedicina ---> ";
		cin>>nuevo->dato;
		cout<<endl;
		
		nuevo->sgte =NULL;
		nuevo->ante=NULL;
		return nuevo;
}

int main() {
	
	
	return 0;
}
