#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include "Universo.h"
using namespace std;

// Informacion de una arista (viaje entre dos planetas)
struct Arista {
    double distancia;      
    double gravitacional;  
    double combustible;    
    bool peligrosa;        // true si la conexion es peligrosa
};

// TAD Grafo: completo, no dirigido, con matriz de adyacencia.
class Grafo {
private:
    int n;                         // cantidad de nodos
    vector<vector<Arista>> matriz; // matriz[i][j]: viaje entre el planeta i y el j

public:
    Grafo();
    void construir(const Universo& u);
    const Arista& obtenerArista(int i, int j) const;
    double obtenerCombustible(int i, int j) const;
    bool esPeligrosa(int i, int j) const;
    int cantidadNodos() const;
};

#endif