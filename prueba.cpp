#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// ==================== ESTRUCTURA ====================
struct Palabra {
    string palabra;
    string traduccion;
    string funcion;
};

// ==================== PROTOTIPOS ====================
vector<Palabra> cargarDiccionario();
void guardarDiccionario(const vector<Palabra>& diccionario);
void agregarVarias();
void mostrar();
void borrar();
void actualizar();
void faseII_traducirCodigo();
bool existeArchivo(const string& nombre);

// ==================== FUNCION PRINCIPAL ====================
int main() {
    int opcion;
    do {
        cout << "\n" << string(60, '=') << "\n";
        cout << "        DICCIONARIO Y TRADUCTOR DE C++ A ESPANOL\n";
        cout << string(60, '=') << "\n";
        cout << "1. Agregar varias palabras\n";
        cout << "2. Mostrar palabras\n";
        cout << "3. Actualizar palabra\n";
        cout << "4. Borrar palabra\n";
        cout << "5. Traducir codigo (Fase II)\n";
        cout << "6. Salir\n";
        cout << string(60, '-') << "\n";
        cout << "Opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: agregarVarias(); break;
            case 2: mostrar(); break;
            case 3: actualizar(); break;
            case 4: borrar(); break;
            case 5: faseII_traducirCodigo(); break;
            case 6: cout << "\nAdios!\n"; break;
            default: cout << "Opcion no valida.\n";
        }
    } while (opcion != 6);

    return 0;
}

// ==================== FUNCIONES DE ARCHIVO ====================

bool existeArchivo(const string& nombre) {
    ifstream f(nombre);
    return f.good();
}

vector<Palabra> cargarDiccionario() {
    vector<Palabra> diccionario;
    ifstream archivo("diccionario.txt");
    if (!archivo) return diccionario;

    string linea;
    while (getline(archivo, linea)) {
        stringstream ss(linea);
        Palabra p;
        getline(ss, p.palabra, '|');
        getline(ss, p.traduccion, '|');
        getline(ss, p.funcion);
        if (!p.palabra.empty())
            diccionario.push_back(p);
    }
    archivo.close();
    return diccionario;
}

void guardarDiccionario(const vector<Palabra>& diccionario) {
    ofstream archivo("diccionario.txt", ios::trunc);
    for (const auto& p : diccionario) {
        archivo << p.palabra << "|" << p.traduccion << "|" << p.funcion << endl;
    }
    archivo.close();
}

// ==================== CRUD ====================

void agregarVarias() {
    ofstream archivo("diccionario.txt", ios::app);
    if (!archivo) {
        cout << "Error al abrir el archivo.\n";
        return;
    }

    string palabra, traduccion, funcion;
    cout << "\nEscriba 'fin' para dejar de ingresar.\n";
    while (true) {
        cout << "\nPalabra: ";
        getline(cin, palabra);
        if (palabra == "fin") break;

        cout << "Traduccion: ";
        getline(cin, traduccion);
        cout << "Funcionalidad: ";
        getline(cin, funcion);

        archivo << palabra << "|" << traduccion << "|" << funcion << endl;
        cout << "Palabra agregada.\n";
    }
    archivo.close();
}

void mostrar() {
    ifstream archivo("diccionario.txt");
    if (!archivo) {
        cout << "No se pudo abrir el archivo.\n";
        return;
    }

    string linea, palabra, traduccion, funcion;
    int contador = 0;

    cout << "\n" << string(80, '=') << "\n";
    cout << "DICCIONARIO COMPLETO\n";
    cout << string(80, '=') << "\n";
    cout << left << setw(20) << "PALABRA" << setw(25) << "TRADUCCION" << "FUNCIONALIDAD\n";
    cout << string(80, '-') << "\n";

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        getline(ss, palabra, '|');
        getline(ss, traduccion, '|');
        getline(ss, funcion);
        cout << left << setw(20) << palabra << setw(25) << traduccion << funcion << endl;
        contador++;
    }

    cout << string(80, '=') << "\n";
    cout << "Total de palabras: " << contador << "\n";
    cout << string(80, '=') << "\n";
    archivo.close();
}

void actualizar() {
    vector<Palabra> diccionario = cargarDiccionario();
    if (diccionario.empty()) {
        cout << "No hay palabras para actualizar.\n";
        return;
    }

    string buscar;
    cout << "Ingrese la palabra a actualizar: ";
    getline(cin, buscar);

    bool encontrado = false;
    for (auto& p : diccionario) {
        if (p.palabra == buscar) {
            cout << "\nPalabra actual: " << p.palabra << "\n";
            cout << "Nueva traduccion: ";
            getline(cin, p.traduccion);
            cout << "Nueva funcionalidad: ";
            getline(cin, p.funcion);
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        guardarDiccionario(diccionario);
        cout << "Palabra actualizada correctamente.\n";
    } else {
        cout << "Palabra no encontrada.\n";
    }
}

void borrar() {
    vector<Palabra> diccionario = cargarDiccionario();
    if (diccionario.empty()) {
        cout << "No hay palabras para borrar.\n";
        return;
    }

    string buscar;
    cout << "Ingrese la palabra que desea eliminar: ";
    getline(cin, buscar);

    bool encontrado = false;
    for (auto it = diccionario.begin(); it != diccionario.end(); ++it) {
        if (it->palabra == buscar) {
            diccionario.erase(it);
            encontrado = true;
            break;
        }
    }

    if (encontrado) {
        guardarDiccionario(diccionario);
        cout << "Palabra eliminada correctamente.\n";
    } else {
        cout << "Palabra no encontrada.\n";
    }
}

// ==================== FASE II: TRADUCTOR ====================

void faseII_traducirCodigo() {
    vector<Palabra> diccionario = cargarDiccionario();
    if (diccionario.empty()) {
        cout << "El diccionario esta vacio. Agregue palabras primero.\n";
        return;
    }

    map<string, string> traducciones;
    for (auto& p : diccionario) {
        traducciones[p.palabra] = p.traduccion;
    }

    cout << "\nIngrese el codigo en C++ (escriba 'FIN' en una linea para terminar):\n";
    string linea;
    vector<string> lineas;

    while (true) {
        getline(cin, linea);
        if (linea == "FIN") break;
        lineas.push_back(linea);
    }

    cout << "\n===== CODIGO TRADUCIDO =====\n";

    for (auto& l : lineas) {
        string palabra, salida = "";
        stringstream ss(l);

        while (ss >> palabra) {
            string limpio = palabra;
            limpio.erase(remove_if(limpio.begin(), limpio.end(),
                [](char c){ return ispunct(c) && c != '_' && c != '{' && c != '}'; }), limpio.end());

            if (traducciones.count(limpio)) {
                size_t pos = palabra.find(limpio);
                if (pos != string::npos)
                    palabra.replace(pos, limpio.size(), traducciones[limpio]);
            }

            salida += palabra + " ";
        }

        // Manejo especial de llaves
        if (l.find("{") != string::npos) {
            if (l.find("if") != string::npos) salida += "inicio si";
            else if (l.find("else") != string::npos) salida += "inicio entonces";
            else if (l.find("for") != string::npos) salida += "inicio para";
            else if (l.find("while") != string::npos) salida += "inicio mientras";
        } 
        if (l.find("}") != string::npos) {
            if (l.find("if") != string::npos) salida += "fin si";
            else if (l.find("else") != string::npos) salida += "fin entonces";
            else if (l.find("for") != string::npos) salida += "fin para";
            else if (l.find("while") != string::npos) salida += "fin mientras";
        }

        cout << salida << endl;
    }

    cout << "=============================\n";
}

