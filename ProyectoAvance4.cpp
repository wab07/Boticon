#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <string>

int ContAntB=10000;
int ContAntF=20000;
int ContAnalgesico=30000;

using namespace std;

struct Lote
{
	int diaIngreso;
	int mesIngreso;
	int anoIngreso;
	int cantidadLote;
	int duracion;
	Lote *sgte;
};

struct MedUnitaria
{
	int idSingular;
	string tipoMedicina;
	int duracion;
	MedUnitaria *sgte;
};



typedef struct Lote *TLote;

TLote anadirLote(){
	TLote nuevo = NULL;
	nuevo = new(struct Lote);
	cout<<"Ingrese la cantidad deseada: "<<endl;
	cin>>nuevo->cantidadLote;
	cout<<"Dia de ingreso: ";
	cin>>nuevo->diaIngreso;
	cout<<"Mes de ingreso: ";
	cin>>nuevo->mesIngreso;
	cout<<"Año de ingreso: ";
	cin>>nuevo->anoIngreso;
	cout<<"Tiempo de vida del lote: ";
	cin>>nuevo->duracion;
	nuevo->sgte=NULL;
	return nuevo;
}

struct Medicina
{
    int idMedicina;
    string tipoMedicina;
    string nombreMedicina;
    int cantMedicina;
    TLote lotes;
    Medicina* sgte;
    Medicina* ante;
};

typedef struct Medicina* TpLista;

enum TipoAccion {
    Agregar,
};

struct Accion {
	TipoAccion tipo;
	TpLista medicina;
	Accion *sgte;
};

typedef Accion* Pila;

void PUSH(Pila &pila, TipoAccion tipo, TpLista medicina) {
    Pila nuevo = new Accion;
    nuevo->tipo = tipo;
    nuevo->medicina = medicina;
    nuevo->sgte = pila;
    pila = nuevo;
}

Accion POP(Pila &pila) {
    if (pila == NULL) return {Agregar, NULL, NULL};
    Accion *t = pila;
    Accion accion = *pila;
    pila = pila->sgte;
    delete t;
    return accion;
}

void Deshacer(Pila &pila, TpLista &lista) {
    Accion accion = POP(pila);
    if (accion.medicina == NULL) {
        cout << "No hay acciones para deshacer." << endl;
        return;
    }
    
    if (accion.tipo == Agregar) {
        cout << "Se elimino la medicina " << accion.medicina->nombreMedicina << " (ID: " << accion.medicina->idMedicina << ")" << endl;
        if (accion.medicina->sgte != NULL) {
            accion.medicina->sgte->ante = accion.medicina->ante;
        }
        if (accion.medicina->ante != NULL) {
            accion.medicina->ante->sgte = accion.medicina->sgte;
        } else {
            lista = accion.medicina->sgte;
        }
        delete accion.medicina;
    }
}


TpLista anadirMedicina()
{
    TpLista nuevo = NULL;
    char tipoMed;
    nuevo = new (struct Medicina);
    cout << "Tipo de Medicina---->" << "(A).- Antibiotico    " << "(B).- Antiinflamatorio    " << "(C).- Analgesico" << endl;
    do
    {
        cin >> tipoMed;
        if (tipoMed != 'A' && tipoMed != 'B' && tipoMed != 'C')
        {
            cout << "ingrese un valor valido" << endl;
        }
    } while (tipoMed != 'A' && tipoMed != 'B' && tipoMed != 'C');
    if (tipoMed == 'A')
    {
        nuevo->tipoMedicina = "Antibiotico";
        cout<<"ID de medicina asignada: "<<endl;
        nuevo->idMedicina=ContAntB+1;
        cout<<nuevo->idMedicina<<endl;
        ContAntB++;
    }
    if (tipoMed == 'B')
    {
        nuevo->tipoMedicina = "Antiinflamatorio";
        cout<<"ID de medicina asignada: "<<endl;
        nuevo->idMedicina=ContAntF+1;    
        cout<<nuevo->idMedicina<<endl;
		ContAntF++;    
    }
    if (tipoMed == 'C')
    {
        nuevo->tipoMedicina = "Analgesico";
        cout<<"ID de medicina asignada "<<endl;
        nuevo->idMedicina=ContAnalgesico+1;
        cout<<nuevo->idMedicina<<endl;
        ContAnalgesico++;
    }
    cin.ignore();
    cout << "ingrese el nombre de la medicina" << endl;
    getline(cin, nuevo->nombreMedicina);
    nuevo->cantMedicina = 0;
	nuevo->lotes =NULL;
    nuevo->sgte = NULL;
    nuevo->ante = NULL;
    return nuevo;
}

void InsertarMedicina(TpLista& lista)
{
    TpLista n = NULL;
    n = anadirMedicina();
    if (lista != NULL)
    {
        n->sgte = lista;
        lista->ante = n;
    }
    lista = n;
}

TpLista BuscarNombre(TpLista lista, string nombreB){
	TpLista t=lista;
	while(t!=NULL&&t->nombreMedicina!=nombreB){
		t=t->sgte;
	}
	return t;
}

void InsertarLote(TpLista lista, string nombreB){
	TpLista medicina=BuscarNombre(lista, nombreB);
	if(medicina!=NULL){
		TLote nuevoLote=anadirLote();
		if(medicina->lotes==NULL){
			medicina->lotes=nuevoLote;
		}else{
			TLote t =medicina->lotes;
			while(t->sgte!=NULL){
				t=t->sgte;
			}
			t->sgte=nuevoLote;
		}
		cout<<"Lote añadido a "<<medicina->nombreMedicina<<endl;
	}	else cout<<"No se encontro una medicina "<<nombreB<<endl;
	
}
void MostrarLista(TpLista lista)
{
	TpLista t=lista;
	cout<<"Lista de medicinas"<<endl;
	while(t!=NULL){
		cout<<t->tipoMedicina<<" : "<<endl;
		cout<<"Lotes de "<<t->nombreMedicina<<": "<<endl;
		TLote lote = t->lotes;
		while(lote !=NULL){
			cout<<"Cantidad de lote: "<<lote->cantidadLote<<" Fecha: "<<lote->diaIngreso<<"/"<<lote->mesIngreso<<"/"<<lote->anoIngreso<<endl;
			lote=lote->sgte;
		}
		cout<<"--------"<<endl;
		t=t->sgte;
	}
}

void menu()
{
	system("CLS");
	cout<<"Fumo"<<endl;
	cout<<"1. Insertar nueva medicina"<<endl;
	cout<<"2. Añadir cantidad de productos a medicina existente"<<endl;
	cout<<"3. Mostrar medicina"<<endl;
}

int main()
{
    TpLista lista = NULL;
	char opc, opc2;
	Pila pila=NULL;
	do{
		menu();
		cin>>opc;
		switch(opc){
			case'1':{
    		InsertarMedicina(lista);
			PUSH(pila, Agregar, lista);	
			system("pause");		
			cout<<"Esta seguro de proceder con la accion?---(y/n(deshara la accion realizada))"<<endl;//pusimos esto por ahora hasta que se cree la GUI
			do{
			cin>>opc2;
			if(opc2!='y'&&opc2!='n'){
				cout<<"Opcion no valida"<<endl;
			}
			}while (opc2!='y'&&opc2!='n');
			if (opc2 == 'n'){
				Deshacer(pila, lista);//la funcion de deshacer estara como un boton luego en la GUI
			}		
				break;
			}
			case'2':{
			string nombreB;
			cout<<"Ingrese el nombre a buscar"<<endl;
			cin>>nombreB;
			InsertarLote(lista,nombreB);
		    system("pause");					
				break;
			}
			case '3':{
				MostrarLista(lista);
		    system("pause");					
				break;
			}
		}
		
	}while(opc!='0');
    return 0;
}

