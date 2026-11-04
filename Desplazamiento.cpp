#include "Desplazamiento.h"
using namespace std;

Desplazamiento::Desplazamiento(int numero, const string& origen, const string& destino,
                               double distancia, double factorG, double combustible,
                               bool peligroso, double acumulado)
    : numero(numero), origen(origen), destino(destino), distancia(distancia),
      factorG(factorG), combustible(combustible), peligroso(peligroso),
      acumulado(acumulado) {}

int Desplazamiento::obtenerNumero() const { return numero; }
const string& Desplazamiento::obtenerOrigen() const { return origen; }
const string& Desplazamiento::obtenerDestino() const { return destino; }
double Desplazamiento::obtenerDistancia() const { return distancia; }
double Desplazamiento::obtenerFactorG() const { return factorG; }
double Desplazamiento::obtenerCombustible() const { return combustible; }
bool Desplazamiento::esPeligroso() const { return peligroso; }
double Desplazamiento::obtenerAcumulado() const { return acumulado; }