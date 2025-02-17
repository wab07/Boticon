#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <string>
#include <chrono>

using namespace std;

enum CategoriaMedicina {
Antibiotico,
Antiinflamatorio,
Analgesico,
};

struct Medicina{
    int idMedicina;
    CategoriaMedicina categoriaMedicina;
    string nombreMedicina;
    int cuMedicina;
    Medicina *sgte;
    Medicina *ante;
};

typedef Medicina *TpLista;

int ValorAleatorio() {
    int min = 100000, max = 999999;
    int num;
	num = rand() % (max - min + 1) + min;
    return num;
}

TpLista CrearMedicina() {
    TpLista n = NULL;
	n = new(struct Medicina);
    char opcion;
	cout<<"\tCreando un NUEVA MEDICINA"<<endl;
    n->idMedicina = ValorAleatorio();
    cout<<"Designando un CODIGO: "<<n->idMedicina<<endl;
    cout<<"Defina la CATEGORIA."<<endl;
	cout<<"Digite [1] para Antibiotico"<<endl;
    cout<<"Digite [2] para Antiinflamatorio"<<endl;
    cout<<"Digite [3] para Analgesico"<<endl;
    cout<<"Ingrese una opcion: ";
    cin>>opcion;
    switch(opcion) {
    	case '1': {
    		n->categoriaMedicina=Antibiotico;
            cout<<"--> Antibiotico"<<endl;
			break;
		}
		
		case '2': {
    		n->categoriaMedicina=Antiinflamatorio;
            cout<<"--> Antiinflamatorio"<<endl;
			break;
		}

        case '3': {
    		n->categoriaMedicina=Analgesico;
            cout<<"--> Analgesico"<<endl;
			break;
		}
	}
    cin.ignore();
    cout<<"Digite el NOMBRE: "; getline(cin,n->nombreMedicina);
    cout<<"Defina la CANTIDAD de Unidades: "; cin>>n->cuMedicina;
    cout<<"\nNUEVA MEDICINA :: Codigo: "<<n->idMedicina<<" | ";
    cout<<"Categoria: ";
	switch(n->categoriaMedicina) {
    	case Antibiotico: {
    		cout<<"Antibiotico";
			break;
		}
		
		case Antiinflamatorio: {
			cout<<"Antiinflamatorio";
			break;
		}

        case Analgesico: {
			cout<<"Analgesico";
			break;
		}
	}
	cout<<" | Nombre: "<<n->nombreMedicina;
    cout<<" | Cantidad de Unidades: "<<n->cuMedicina<<endl;
	n->ante=nullptr;
	n->sgte=nullptr;
    return n;
}

void InsertarMedicinaInicio(TpLista &lista, TpLista n){
	if(lista != nullptr){
			n->sgte = lista;
			lista->ante=n;
	}
	lista=n;
}

void InsertarMedicinaFinal(TpLista &lista, TpLista n){
	TpLista t=lista;
	if(lista == nullptr)
		lista=n;
	else{
		while(t->sgte != nullptr){
            t=t->sgte;
        }
		t->sgte = n;
		n->ante=t;			
	}
}

void menu(){
	system("cls");
	cout<<"\nSISTEMA DE ALMACENAMIENTO DE NODOS AB\n\n";
	cout<<"1.- Anyadir una MEDICINA"<<endl<<endl;
	cout<<"Digite una Opcion: ";
}

int main() {
    srand(time(0));
    TpLista lista = NULL;
    int idMedicina;
    CategoriaMedicina categoriaMedicina;
    string nombreMedicina;
    int cuMedicina;
	char opcion;
	do {
		menu(); cin>>opcion;
		cout<<endl;
		switch(opcion) {
			case '1':{
                lista = CrearMedicina();
			break;
            }

			case '2':{
				
			break;
            }

			case '3':{
				
			break;
            }

			case '4':{
				
			break;
            }
			
            case '5':{
				
			break;
            }

			case '0':{
				
				cout<<"Saliendo del programa..."<<endl;
				
			break;
            }
			
			default:{
				
				cout<<"\nDigite una OPCION VALIDA"<<endl;
				
			break;
            }
		}
		
		cout<<"\nPresione cualquier tecla para continuar..."<<endl;
        cin.ignore();
        cin.get();
		
	} while(opcion != '0');
}
