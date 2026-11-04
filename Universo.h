#ifndef UNIVERSO_H
#define UNIVERSO_H

#include <string>
#include <vector>
#include "Planeta.h"
using namespace std;

// TAD Universo: conjunto de planetas y parametros de la mision (k, lambda).
class Universo {
private:
    double k;                 // constante base de consumo de combustible
    double lambda;            // coeficiente de sensibilidad gravitacional
    vector<Planeta> planetas; // la posicion en el vector es el indice del planeta

public:
    Universo(double k, double lambda);

    void agregarPlaneta(const Planeta& p);

    // Verifica las reglas del enunciado. Si algo falla, deja la causa en 'mensaje'.
    bool validar(string& mensaje) const;

    double obtenerK() const;
    double obtenerLambda() const;
    int obtenerIndice(const string& nombre) const;  // -1 si no existe
    const Planeta& obtenerPlaneta(int i) const;
    int cantidadPlanetas() const;
};

#endif