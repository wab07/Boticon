#include <iostream>
#include <cstdlib>
#include <ctime>
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

enum TipoAccion {
    Agregar,
    Eliminar
};

struct Accion {
	TipoAccion tipo;
	TpLista medicina;
	Accion *sgte;
};

typedef Accion* Pila;

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

void PUSH(Pila &pila, TipoAccion tipo, TpLista medicina) {
    Accion *nuevo = new Accion;
    nuevo->tipo = tipo;
    nuevo->medicina = medicina;
    nuevo->sgte = pila;
    pila = nuevo;
}

Accion POP(Pila &pila) {
    if (pila == nullptr) return {Agregar, nullptr, nullptr};
    Accion *t = pila;
    Accion accion = *pila;
    pila = pila->sgte;
    delete t;
    return accion;
}

void Deshacer(Pila &pila, TpLista &lista) {
    Accion accion = POP(pila);
    if (accion.medicina == nullptr) {
        cout << "No hay acciones para deshacer." << endl;
        return;
    }
    
    if (accion.tipo == Agregar) {
        cout << "Se elimino la medicina " << accion.medicina->nombreMedicina << " (ID: " << accion.medicina->idMedicina << ")" << endl;
        if (accion.medicina->sgte != nullptr) {
            accion.medicina->sgte->ante = accion.medicina->ante;
        }
        if (accion.medicina->ante != nullptr) {
            accion.medicina->ante->sgte = accion.medicina->sgte;
        } else {
            lista = accion.medicina->sgte;
        }
        delete accion.medicina;
    }
}


void menu(){
	system("cls");
	cout<<"\nSISTEMA DE ALMACENAMIENTO DE NODOS AB\n\n";
	cout<<"1.- Agregar una MEDICINA"<<endl;
	cout<<"2.- Deshacer ultima accion"<<endl<<endl;
	cout<<"Digite una Opcion: ";
}

int main() {
    srand(time(0));
    TpLista lista = nullptr;
    Pila pila=nullptr;
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
                TpLista nuevaMedicina = CrearMedicina();
                InsertarMedicinaInicio(lista, nuevaMedicina);
                PUSH(pila, Agregar, nuevaMedicina);
			break;
            }

			case '2':{
				Deshacer(pila, lista);
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