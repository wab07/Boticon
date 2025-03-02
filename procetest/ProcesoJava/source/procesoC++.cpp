#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>

using namespace std;

// Estructura para almacenar un lote
struct Lote {
    string nombre;     // Nombre de la medicina
    string tipo;       // Tipo de la medicina
    int cantidad;      // Cantidad de unidades en el lote
    int idMedicina;    // ID de la medicina
    int duracion;      // Duración en días
    int diaIngreso;    // Día de ingreso
    int mesIngreso;    // Mes de ingreso
    int anoIngreso;    // Año de ingreso
    Lote* sgte;        // Siguiente nodo en la lista
};

typedef Lote* TpLote;

// Crear un nodo de lote
Lote* CrearLote(const string& nombre, const string& tipo, int cantidad, int idMedicina, int duracion) {
    Lote* nuevo = new Lote;
    nuevo->nombre = nombre;
    nuevo->tipo = tipo;
    nuevo->cantidad = cantidad;
    nuevo->idMedicina = idMedicina;
    nuevo->duracion = duracion;
    nuevo->diaIngreso = 0; // Placeholder
    nuevo->mesIngreso = 0;
    nuevo->anoIngreso = 0;
    nuevo->sgte = NULL;
    return nuevo;
}

// Insertar un lote en la lista
void InsertarLote(TpLote& lista, Lote* nuevo) {
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

// Cargar lotes desde un archivo
void CargarLotes(TpLote& lista, const string& archivo) {
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

        Lote* nuevo = CrearLote(nombre, tipo, cantidad, idMedicina, duracion);
        InsertarLote(lista, nuevo);
    }
    file.close();
}

// Guardar lotes con fechas placeholder
void GuardarLotesPlaceholder(TpLote lista, const string& archivo) {
    ofstream file(archivo);
    if (!file.is_open()) {
        cout << "No se pudo abrir el archivo: " << archivo << endl;
        return;
    }
    Lote* temp = lista;
    while (temp) {
        file << temp->nombre << "," << temp->tipo << "," << temp->cantidad << ","
             << temp->idMedicina << "," << temp->duracion << ","
             << temp->diaIngreso << "," << temp->mesIngreso << "," << temp->anoIngreso << "\n";
        temp = temp->sgte;
    }
    file.close();
}

// Ejecutar programa Java para actualizar las fechas
void EjecutarProgramaJava() {
    string comando = "java -cp ProcesoJava/bin proceso.ActualizarFechas ../lotes_placeholder.txt ../lotes_actualizados.txt";;
    int resultado = system(comando.c_str());
    if (resultado == 0) {
        cout << "El programa Java se ejecutó correctamente." << endl;
    } else {
        cout << "Hubo un error al ejecutar el programa Java." << endl;
    }
}

// Actualizar lotes con fechas reales desde el archivo actualizado
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

        Lote* temp = lista;
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

// Imprimir lotes actualizados
void ImprimirLotes(TpLote lista) {
    Lote* temp = lista;
    while (temp) {
        cout << temp->nombre << " (" << temp->tipo << "), ID: " << temp->idMedicina
             << ", Fecha: " << temp->diaIngreso << "/" << temp->mesIngreso << "/" << temp->anoIngreso << endl;
        temp = temp->sgte;
    }
}

int main() {
    TpLote lista = NULL;

    // Paso 1: Cargar lotes iniciales
    CargarLotes(lista, "medicinas.txt");

    // Paso 2: Guardar lotes con fechas placeholder
    GuardarLotesPlaceholder(lista, "lotes_placeholder.txt");

    // Paso 3: Ejecutar programa Java para actualizar las fechas
    EjecutarProgramaJava();

    // Paso 4: Actualizar las fechas de los lotes desde el archivo actualizado
    ActualizarFechasLotes(lista, "lotes_actualizados.txt");

    // Paso 5: Imprimir los lotes actualizados
    ImprimirLotes(lista);

    return 0;
}
