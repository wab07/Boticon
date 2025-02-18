#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <string>
#include <chrono>

using namespace std;

struct Medicina
{
    int idMedicina;
    string tipoMedicina;
    string nombreMedicina;
    int cantMedicina;
    Medicina *sgte;
    Medicina *ante;
};

typedef struct Medicina *TpLista;
TpLista anadirMedicina()
{
    TpLista nuevo = NULL;
    char tipoMed;
    nuevo = new (struct Medicina);
    cout << "Ingresar idMedicina ---> ";
    cin >> nuevo->idMedicina;
    cout << endl;
    cout << "Tipo de Medicina---->" << "(A).- Antibiotico    " << "(B).- Antiinflamatorio    " << "(C).- Analgesico" << endl;
    do
    {
        cin >> tipoMed;
        if (tipoMed != 'A' && tipoMed != 'B' && tipoMed != 'C')
        {
            cout << "ingrese un valor valido" << endl;
        }
    } while (tipoMed != 'A' && tipoMed != 'B' && tipoMed != 'C');
    if (tipoMed = 'A')
    {
        nuevo->tipoMedicina = "Antibiotico";
    }
    if (tipoMed = 'B')
    {
        nuevo->tipoMedicina = "Antiinflamatorio";
    }
    if (tipoMed = 'C')
    {
        nuevo->tipoMedicina = "Analgesico";
    }
    cin.ignore();
    cout << "ingrese el nombre de la medicina" << endl;
    getline(cin, nuevo->nombreMedicina);
    nuevo->cantMedicina = 0;

    nuevo->sgte = NULL;
    nuevo->ante = NULL;
    return nuevo;
}

void InsertarMedicina(TpLista &lista)
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

void MostrarLista(TpLista lista)
{

    int i = 0;
    TpLista t = lista, aux = NULL;
    cout << "Lista de medicinas" << endl;
    while (t != NULL)
    {
        cout << i + 1 << ") " << lista->idMedicina << " " << lista->nombreMedicina << " " << lista->tipoMedicina << endl;
        aux = t;
        t = t->sgte;
        i++;
    }
}

void menu()
{
    system("CLS");
    cout << "\t\nLISTA CIRCULAR DOBLEMENTE ENLAZADA" << endl
         << endl;
    cout << "1.- Insertar al Inicio" << endl;
    cout << "2.- Insertar al Final" << endl;
    cout << "3.- Insertar por posicion" << endl;
    cout << "4.- Mostrar Lista IDA Y VUELTA" << endl
         << endl;
    cout << "5.- Eliminar primer nodo" << endl;
    cout << "6.- Eliminar ultimo nodo" << endl;
    cout << "7.- Eliminar por Posicion" << endl;
    cout << "8.- Buscar y Reemplazar valor de un nodo" << endl
         << endl;
    cout << "0.- Salir del menu" << endl
         << endl;
    cout << " Ingresar opcion ---> ";
}

int main()
{
    TpLista lista = NULL;
    cout << "viwas" << endl;
    InsertarMedicina(lista);
    MostrarLista(lista);
    system("pause");
    InsertarMedicina(lista);
    return 0;
}
