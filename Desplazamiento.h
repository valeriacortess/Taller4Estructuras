#ifndef DESPLAZAMIENTO_H
#define DESPLAZAMIENTO_H

#include <string>
using namespace std;

// TAD Desplazamiento: registro de un viaje realizado por la nave.
class Desplazamiento {
private:
    int numero;          // numero del desplazamiento (1, 2, 3...)
    string origen;
    string destino;
    double distancia;
    double factorG;      // factor de ajuste gravitacional
    double combustible;  // combustible consumido en este viaje
    bool peligroso;      // true si la conexion usada era peligrosa
    double acumulado;    // combustible acumulado hasta este viaje

public:
    Desplazamiento(int numero, const string& origen, const string& destino,
                   double distancia, double factorG, double combustible,
                   bool peligroso, double acumulado);

    int obtenerNumero() const;
    const string& obtenerOrigen() const;
    const string& obtenerDestino() const;
    double obtenerDistancia() const;
    double obtenerFactorG() const;
    double obtenerCombustible() const;
    bool esPeligroso() const;
    double obtenerAcumulado() const;
};

#endif