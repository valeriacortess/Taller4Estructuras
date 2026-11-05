#ifndef PLANETA_H
#define PLANETA_H

#include <string>
#include <vector>
using namespace std;

// TAD Planeta - un nodo del grafo.
class Planeta {
private:
    string nombre;              
    double x, y, z;            
    double t;                   
    vector<string> peligrosos;  // nombres de planetas con conexion peligrosa

public:
    Planeta(const string& nombre, double x, double y, double z, double t);

    const string& obtenerNombre() const;
    double obtenerX() const;
    double obtenerY() const;
    double obtenerZ() const;
    double obtenerT() const;
    const vector<string>& obtenerPeligrosos() const;

    void agregarPeligroso(const string& destino);
    bool esPeligrosoCon(const string& planetica) const;

    // Distancia euclidiana 3D entre este planeta y otro
    double distanciaA(const Planeta& planetica) const;
};

#endif
