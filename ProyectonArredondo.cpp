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
    	char tipoMed;
    	nuevo= new(struct Medicina);
    	cout<<"Ingresar idMedicina ---> ";
		cin>>nuevo->idMedicina;
		cout<<endl;
		cout<<"Tipo de Medicina---->"<<"(A).- Antibiotico    "<<"(B).- Antiinflamatorio    "<<"(C).- Analgesico"<<endl;
		do{
		cin<<tipoMed;
		if(tipoMed!= 'A'&& tipoMed!= 'B' && tipoMed!= 'C'){
			cout<<"ingrese un valor valido"<<endl;
		}
		}while(tipoMed!= 'A'&& tipoMed!= 'B' && tipoMed!= 'C');
		
		nuevo->sgte =NULL;
		nuevo->ante=NULL;
		return nuevo;
}

int main() {
	
	
	return 0;
}
