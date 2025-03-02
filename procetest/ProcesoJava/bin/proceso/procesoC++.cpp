#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;


struct Lote {
    string nombre;     
    string tipo;       
    int cantidad;      
    int idMedicina;    
    int duracion;      
    int diaIngreso;    
    int mesIngreso;    
    int anoIngreso;    
    Lote* sgte;        
};

typedef Lote* TpLote;


TpLote CrearLote(const string &nombre, const string &tipo, int cantidad, int idMedicina, int duracion) {
    TpLote nuevo = new Lote;
    nuevo->nombre = nombre;
    nuevo->tipo = tipo;
    nuevo->cantidad = cantidad;
    nuevo->idMedicina = idMedicina;
    nuevo->duracion = duracion;
    nuevo->diaIngreso = 0; 
    nuevo->mesIngreso = 0;
    nuevo->anoIngreso = 0;
    nuevo->sgte = NULL;
    return nuevo;
}


void InsertarLote(TpLote &lista, TpLote nuevo) {
    if (!lista) {
        lista = nuevo;
    } else {
        Lote* temp = lista;
        while (temp->sgte) {
            temp = temp->sgte;
        }
        temp->sgte = nuevo;
    }
}


void CargarLotes(TpLote &lista, const string &archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }
    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string nombre, tipo, cantidadStr, idStr, duracionStr;
        getline(ss, nombre, ',');
        getline(ss, tipo, ',');
        getline(ss, cantidadStr, ',');
        getline(ss, idStr, ',');
        getline(ss, duracionStr, ',');

        int cantidad = stoi(cantidadStr);
        int idMedicina = stoi(idStr);
        int duracion = stoi(duracionStr);

        TpLote nuevo = CrearLote(nombre, tipo, cantidad, idMedicina, duracion);
        InsertarLote(lista, nuevo);
    }
    file.close();
}


void GuardarLotesPlaceholder(TpLote lista, const string &archivo) {
    ofstream file(archivo);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }
    TpLote temp = lista;
    while (temp!=NULL) {
        file << temp->nombre << "," << temp->tipo << "," << temp->cantidad << "," << temp->idMedicina << "," << temp->duracion << ","<< temp->diaIngreso << "," << temp->mesIngreso << "," << temp->anoIngreso <<endl;
        temp = temp->sgte;
    }
    file.close();
}


void EjecutarProgramaJava() {
	
    string comando = "cd C:/Users/DELL/Desktop/Procetest/ProcesoJava && java -cp bin proceso.ActualizarFechas bin/proceso/lotes_placeholder.txt bin/proceso/lotes_actualizados.txt";
    int resultado = system(comando.c_str());
    if (resultado == 0) {
        cout << "Se genero las nuevas listas actualizadas." << endl;
    } else {
        cout << "Hubo un error al actualizar las listas." << endl;
    }
}


void ActualizarFechasLotes(TpLote lista, const string& archivo) {
    ifstream file(archivo);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }
    string linea;
    while (getline(file, linea)) {
        stringstream ss(linea);
        string nombre, tipo, cantidadStr, idStr, duracionStr, diaStr, mesStr, anoStr;
        getline(ss, nombre, ',');
        getline(ss, tipo, ',');
        getline(ss, cantidadStr, ',');
        getline(ss, idStr, ',');
        getline(ss, duracionStr, ',');
        getline(ss, diaStr, ',');
        getline(ss, mesStr, ',');
        getline(ss, anoStr, ',');

        int cantidad = stoi(cantidadStr);
        int idMedicina = stoi(idStr);
        int duracion = stoi(duracionStr);
        int dia = stoi(diaStr);
        int mes = stoi(mesStr);
        int ano = stoi(anoStr);

       TpLote temp = lista;
        while (temp) {
            if (temp->nombre == nombre && temp->idMedicina == idMedicina) {
                temp->diaIngreso = dia;
                temp->mesIngreso = mes;
                temp->anoIngreso = ano;
                break;
            }
            temp = temp->sgte;
        }
    }
    file.close();
}


void ImprimirLotes(TpLote lista) {
    TpLote temp = lista;
    while (temp!=NULL) {
        cout << temp->nombre << " (" << temp->tipo << "), ID: " << temp->idMedicina<< ", Fecha: " << temp->diaIngreso << "/" << temp->mesIngreso << "/" << temp->anoIngreso << endl;
        temp = temp->sgte;
    }
}

int main() {
    TpLote lista = NULL;

    
    CargarLotes(lista, "medicinas.txt");

  
    GuardarLotesPlaceholder(lista, "lotes_placeholder.txt");

    
    EjecutarProgramaJava();

   
    ActualizarFechasLotes(lista, "lotes_actualizados.txt");

    
    ImprimirLotes(lista);

    return 0;
}
