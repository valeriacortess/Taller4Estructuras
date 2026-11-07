#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Planeta.h"
#include "Universo.h"
#include "Grafo.h"
#include "Mision.h"

using namespace std;


// Función que lee el archivo de entrada y construye el Universo
bool leerEntrada(const string& nombreArchivo, Universo& universo, string& mensajeError) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        mensajeError = "No se pudo abrir el archivo: " + nombreArchivo;
        return false;
    }

    double k, lambda;
    int m;

    // Primera línea, k lambda
    if (!(archivo >> k >> lambda)) {
        mensajeError = "Error al leer k y lambda";
        return false;
    }

    // Segunda línea, cantidad de planetas
    if (!(archivo >> m)) {
        mensajeError = "Error al leer la cantidad de planetas (m)";
        return false;
    }

    if (m <= 0) {
        mensajeError = "La cantidad de planetas debe ser mayor que 0";
        return false;
    }

    // Se crea el universo con los parámetros leídos
    universo = Universo(k, lambda);

    // Se leen los m planetas
    for (int i = 0; i < m; i++) {
        string nombre;
        double x, y, z, t;
        int p;  // cantidad de conexiones peligrosas

        if (!(archivo >> nombre >> x >> y >> z >> t >> p)) {
            mensajeError = "Error al leer los datos del planeta número " + to_string(i + 1);
            return false;
        }

        Planeta planeta(nombre, x, y, z, t);

        // Se leen las p conexiones peligrosas
        for (int j = 0; j < p; j++) {
            string destino;
            if (!(archivo >> destino)) {
                mensajeError = "Error al leer conexiones peligrosas del planeta " + nombre;
                return false;
            }
            planeta.agregarPeligroso(destino);
        }

        universo.agregarPlaneta(planeta);
    }

    archivo.close();
    return true;
}


// Programa principal

int main(int argc, char* argv[]) {
    // Nombre del archivo de entrada
    string archivoEntrada;

    if (argc >= 2) {
        archivoEntrada = argv[1];
    } else {
        // Si no se pasa argumento, se usa un nombre por defecto
        archivoEntrada = "entrada.txt";
        cout << "No se especificó archivo de entrada. Se usará: " << archivoEntrada << endl;
    }

    // 1. Leer el archivo de entrada
    Universo universo(0.0, 0.0);
    string mensajeError;

    if (!leerEntrada(archivoEntrada, universo, mensajeError)) {
        cerr << "Error de lectura: " << mensajeError << endl;
        return 1;
    }

    // 2. Validar los datos
    if (!universo.validar(mensajeError)) {
        cerr << "Error de validación: " << mensajeError << endl;
        return 1;
    }

    cout << "Datos cargados y validados correctamente." << endl;
    cout << "Planetas: " << universo.cantidadPlanetas() << endl;

    // 3. Construir el grafo
    Grafo grafo;
    grafo.construir(universo);

    // 4. Ejecutar la misión
    Mision mision(universo, grafo);
    mision.ejecutar();

    cout << "Algoritmo ejecutado. Desplazamientos realizados: "
         << mision.obtenerDesplazamientos().size() << endl;

    // 5. Generar archivos de salida
    string archivoDetalle = "detalle_recorrido.txt";
    string archivoResumen = "resumen_mision.txt";

    if (!mision.escribirDetalle(archivoDetalle)) {
        cerr << "Error al escribir el archivo de detalle." << endl;
        return 1;
    }

    if (!mision.escribirResumen(archivoResumen)) {
        cerr << "Error al escribir el archivo de resumen." << endl;
        return 1;
    }

    cout << "Archivos generados correctamente:" << endl;
    cout << "  - " << archivoDetalle << endl;
    cout << "  - " << archivoResumen << endl;

    return 0;
}
