#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <string>
#include <limits>

using namespace std;

int ContAntB=10000;
int ContAntF=20000;
int ContAnalgesico=30000;

enum TipoAccion {
    Agregar,
};

enum categoriaMedicina {
	Antibiotico,
	Antiinflamatorio,
	Analgesico,
};

struct Lote {
	int diaIngreso;
	int mesIngreso;
	int anoIngreso;
	int cantidadLote;
	int duracion;
	Lote *sgte;
};

struct MedUnitaria {
	int idSingular;
	string tipoMedicina;
	int duracion;
	MedUnitaria *sgte;
};

void LimpiarErrores() {
    cout << "\033[A\33[2K";  // Borra línea de "Presiona ENTER para continuar"
    cout << "\033[A\33[2K";  // Borra línea de "Entrada inválida"
    cout << "\033[A\33[2K";  // Borra línea de "Digite una opción: X"
}

int LeerNum() {
    string input;
    int num;
    while (true) {
        getline(cin, input);
        try {
            num = stoi(input); // Intenta convertir la entrada a entero
            return num; // Si es válido, lo devuelve
        } catch (...) {
            cout<<"Entrada INVALIDA. Intente de nuevo.\n";
            cout<<"Presiona ENTER para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Espera ENTER
            LimpiarErrores();
            cout<<"Digite una opcion: ";
        }
    }
}

char LeerCaracter() {
    string input;
    while (true) {    
        getline(cin, input);
        if (input.length() != 1) {  // Si la entrada no es exactamente un carácter
            cout<<"Entrada INVALIDA. Intente de nuevo.\n";
            cout<<"Presiona ENTER para continuar...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Espera ENTER
            LimpiarErrores();
            cout<<"Digite una opcion: ";
        } else {
            return input[0];  // Devuelve el único carácter ingresado
        }
    }
}

typedef struct Lote *TLote;

TLote anadirLote(){
	TLote nuevo = NULL;
	nuevo = new(struct Lote);
	cout<<"\tNUEVO LOTE"<<endl;
	cout<<"Ingrese la cantidad deseada: "; nuevo->cantidadLote = LeerNum();
	cout<<"Dia de ingreso: "; nuevo->diaIngreso = LeerNum();
	cout<<"Mes de ingreso: "; nuevo->mesIngreso = LeerNum();
	cout<<"Anyo de ingreso: "; nuevo->anoIngreso = LeerNum();
	cout<<"Tiempo de vida del lote: "; nuevo->duracion = LeerNum();
	nuevo->sgte=NULL;
	return nuevo;
}

struct Medicina {
    int idMedicina;
    categoriaMedicina CategoriaMedicina;
    string tipoMedicina;
    string nombreMedicina;
    int cantMedicina;
    TLote lotes;
    Medicina* sgte;
    Medicina* ante;
};

typedef struct Medicina* TpLista;

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

void MostrarListaMedicinas(TpLista lista) {
	TpLista t=lista;
	if(lista != NULL){
		cout<<"\tLISTA DE MEDICINAS."<<endl;
		cout<<"\t------------------"<<endl;
		while(t!=NULL){
			cout<<"MEDICINA :: Nombre de Marca: "<<t->nombreMedicina<<" | Categoria: "<<t->tipoMedicina<<" | "<<endl;
			TLote lote = t->lotes;
			cout<<"-----------------------------------------------------"<<endl;
			t=t->sgte;
		}
	} else {
		cout<<"\tLa LISTA DE MEDICINAS esta vacia."<<endl;
	}
}

void MostrarListaMedicinasLote(TpLista lista) {
	TpLista t=lista;
	if(lista != NULL){
		cout<<"\tLISTA DE MEDICINAS CON LOTE."<<endl;
		cout<<"\t---------------------------"<<endl;
		while(t!=NULL){
			cout<<"MEDICINA :: Nombre de Marca: "<<t->nombreMedicina<<" | Categoria: "<<t->tipoMedicina<<" | ";
			TLote lote = t->lotes;
			while(lote !=NULL){
				cout<<"Cantidad por lote: "<<lote->cantidadLote<<" | Fecha de Ingreso: "<<lote->diaIngreso<<"/"<<lote->mesIngreso<<"/"<<lote->anoIngreso<<endl;
				lote=lote->sgte;
			}
			cout<<" | "<<endl;
			cout<<"-----------------------------------------------------------------------------------------------------------"<<endl;
			t=t->sgte;
		}
	} else {
		cout<<"\tLa LISTA DE MEDICINAS CON LOTE esta vacia."<<endl;
	}
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
    
    switch(accion.medicina->CategoriaMedicina) {
    	case Antibiotico: {
    		ContAntB--;
			break;
		}
		
		case Antiinflamatorio: {
    		ContAntF--;
			break;
		}
		
		case Analgesico: {
    		ContAnalgesico--;
			break;
		}
	}
}

void PreguntarDeshacer(Pila &pila, TpLista &lista, char opc2) {
	system("pause");		
	cout<<"\n\tDesea proceder con la accion?"<<endl;//pusimos esto por ahora hasta que se cree la GUI
	cout<<"-> Digite 1 para MANTENER accion realizada"<<endl;
	cout<<"-> Digite 2 para DESHACER accion realizada"<<endl;
	cout<<"Digite una opcion: ";
	do{
		opc2 = LeerCaracter();
		if(opc2!='1'&&opc2!='2'){
		cout<<"Opcion no valida"<<endl;
		}
	}while (opc2!='1'&&opc2!='2');
	
	if (opc2 == '2'){
		Deshacer(pila, lista);//la funcion de deshacer estara como un boton luego en la GUI
	}		
}

TpLista anadirMedicina() {
    TpLista nuevo = NULL;
    char opcion;
    nuevo = new (struct Medicina);
    cout<<"\tNUEVA MEDICINA"<<endl;
	cout<<"CATEGORIA de Medicina"<<endl; 
	cout<<"(1).- Antibiotico    (2).- Antiinflamatorio    (3).- Analgesico"<<endl;
    cout<<"Digite una opcion: ";
	do{
        opcion = LeerCaracter();
        if (opcion!='1' && opcion!='2' && opcion!='3') {
            cout<<"Ingrese una opcion valida."<<endl;
        }
    } while (opcion!='1' && opcion!='2' && opcion!='3');
    
    cout<<endl;
    switch(opcion) {
    	case '1': {
    		nuevo->CategoriaMedicina = Antibiotico;
	        nuevo->tipoMedicina = "Antibiotico";
	        cout<<"ID de medicina asignada: ";
	        nuevo->idMedicina=ContAntB+1;
	        cout<<nuevo->idMedicina<<endl;
			break;
		}
		
		case '2': {
			nuevo->CategoriaMedicina = Antiinflamatorio;
			nuevo->tipoMedicina = "Antiinflamatorio";
	        cout<<"ID de medicina asignada: ";
	        nuevo->idMedicina=ContAntF+1;    
	        cout<<nuevo->idMedicina<<endl;
			ContAntF++;  
			break;
		}
		
		case '3': {
			nuevo->CategoriaMedicina = Analgesico;
			nuevo->tipoMedicina = "Analgesico";
	        cout<<"ID de medicina asignada ";
	        nuevo->idMedicina=ContAnalgesico+1;
	        cout<<nuevo->idMedicina<<endl;
	        ContAnalgesico++;
			break;
		}
	}
    
    cin.ignore();
    cout<<"Digite el Nombre de la MARCA de la Medicina: ";
    getline(cin, nuevo->nombreMedicina);
    nuevo->cantMedicina = 0;
	nuevo->lotes=NULL;
    nuevo->sgte=NULL;
    nuevo->ante=NULL;
    return nuevo;
}

void InsertarMedicina(TpLista& lista) {
    TpLista n = NULL;
    n = anadirMedicina();
    if (lista != NULL)
    {
        n->sgte = lista;
        lista->ante = n;
    }
    lista = n;
}

TpLista BuscarNombre(TpLista lista, string nombreB) {
	TpLista t=lista;
	while(t!=NULL&&t->nombreMedicina!=nombreB){
		t=t->sgte;
	}
	return t;
}

void InsertarLote(TpLista lista, string nombreB) {
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
		cout<<"Lote ANYADIDO a la marca de medicinas \""<<medicina->nombreMedicina<<"\""<<endl;
		cout<<endl;
		MostrarListaMedicinasLote(lista);
	}else{
		cout<<"NO se encontro una medicina \""<<nombreB<<"\""<<endl;
	}
}



void menu() {
	system("CLS");
	cout<<"\n\tBOTICAS CHOKAPU"<<endl<<endl;
	cout<<"1. Insertar NUEVA medicina."<<endl;
	cout<<"2. Determinar la CANTIDAD DE PRODUCTOS de una medicina existente."<<endl;
	cout<<"3. MOSTRAR medicina SIN lote."<<endl<<endl;
	cout<<"0. Salir del programa."<<endl<<endl;
	cout<<"Digite una opcion: ";
}

int main() {
    TpLista lista = NULL;
	char opc, opc2;
	Pila pila=NULL;
	do{
		menu();
		opc = LeerCaracter();
		cout<<endl;
		switch(opc){
			case'1':{
	    		InsertarMedicina(lista);
				PUSH(pila, Agregar, lista);
				cout<<endl;
				PreguntarDeshacer(pila, lista, opc2);
				break;
			}
			
			case'2':{
				string nombreB; TpLista w = NULL;
				w = lista;
				MostrarListaMedicinas(lista);
				cout<<endl;
				if(lista != NULL) {
					cout<<"Digite el NOMBRE DE MARCA a buscar: "; cin>>nombreB;
					cout<<endl;
					InsertarLote(lista,nombreB);
				}
			    system("pause");					
				break;
			}
			
			case '3':{
				MostrarListaMedicinas(lista);
		    	system("pause");					
				break;
			}
		}
		
	}while(opc!='0');
    return 0;
}
