#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct MedicinaUnitaria {
    string nombre;     
    string tipo;       
    int cantidad;      
    int idMedicina;    
    int duracion;      
    int diaIngreso;   
    int mesIngreso;    
    int anoIngreso;
    int diaIngresoRes;
    int mesIngresoRes;
    int anoIngresoRes;
    int duracionRes;
    int cantidadRes;
    MedicinaUnitaria* sgte;
};

typedef MedicinaUnitaria* TpMedu;

TpMedu CrearMedu(const string &nombre, const string &tipo, int cantidad, int idMedicina, int duracion, int diaIngreso, int mesIngreso, int anoIngreso) {
    TpMedu nuevo = new MedicinaUnitaria;
    nuevo->nombre = nombre;
    nuevo->tipo = tipo;
    nuevo->cantidad = cantidad;
    nuevo->idMedicina = idMedicina;
    nuevo->duracion = duracion;
    nuevo->diaIngreso = diaIngreso;
    nuevo->mesIngreso = mesIngreso;
    nuevo->anoIngreso = anoIngreso;

    nuevo->diaIngresoRes = diaIngreso + 3;
    nuevo->mesIngresoRes = mesIngreso;
    nuevo->anoIngresoRes = anoIngreso;
    nuevo->duracionRes = duracion - 5;
    nuevo->cantidadRes = cantidad / 2;

    nuevo->sgte = nullptr;
    return nuevo;
}

void AnyadirMedu(TpMedu &cola, TpMedu nuevo) {
    if (cola == nullptr) {
        cola = nuevo;
    } else {
        TpMedu temp = cola;
        while (temp->sgte != nullptr) {
            temp = temp->sgte;
        }
        temp->sgte = nuevo;
    }
}

void CargarMedu(TpMedu &lista, const string &archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }

    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string nombre, tipo;
        int cantidad, idMedicina, duracion, diaIngreso, mesIngreso, anoIngreso;

        getline(ss, nombre, ',');
        getline(ss, tipo, ',');
        ss >> cantidad; ss.ignore();
        ss >> idMedicina; ss.ignore();
        ss >> duracion; ss.ignore();
        ss >> diaIngreso; ss.ignore();
        ss >> mesIngreso; ss.ignore();
        ss >> anoIngreso;

        TpMedu nuevo = CrearMedu(nombre, tipo, cantidad, idMedicina, duracion, diaIngreso, mesIngreso, anoIngreso);
        AnyadirMedu(lista, nuevo);
    }

    file.close();
}

void ExportarMedu(TpMedu lista, const string &archivo) {
    ofstream file(archivo);
    if (!file.is_open()) {
        cout << "No se pudo crear el archivo: " << archivo << endl;
        return;
    }

    while (lista != nullptr) {
        file << lista->nombre << "," << lista->tipo << "," << lista->cantidad << "," 
             << lista->idMedicina << "," << lista->duracion << "," 
             << lista->diaIngreso << "," << lista->mesIngreso << "," << lista->anoIngreso << ","
             << lista->diaIngresoRes << "," << lista->mesIngresoRes << "," << lista->anoIngresoRes << ","
             << lista->duracionRes << "," << lista->cantidadRes << endl;
        lista = lista->sgte;
    }

    file.close();
    cout << "Archivo exportado correctamente como " << archivo << endl;
}

void MostrarMedu(TpMedu lista) {
    while (lista != nullptr) {
        cout << "Nombre: " << lista->nombre << ", Tipo: " << lista->tipo 
             << ", Cantidad: " << lista->cantidad << ", ID: " << lista->idMedicina 
             << ", Duracion: " << lista->duracion 
             << ", Ingreso: " << lista->diaIngreso << "/" << lista->mesIngreso << "/" << lista->anoIngreso
             << ", Ingreso Reserva: " << lista->diaIngresoRes << "/" << lista->mesIngresoRes << "/" << lista->anoIngresoRes
             << ", Duracion Reserva: " << lista->duracionRes 
             << ", Cantidad Reserva: " << lista->cantidadRes
             << endl;
        lista = lista->sgte;
    }
}

int main() {
    TpMedu colaMedu = nullptr;
    CargarMedu(colaMedu, "lotes_actualizados.txt");
    MostrarMedu(colaMedu);
    ExportarMedu(colaMedu, "lotes_wasa.txt");
    return 0;
}