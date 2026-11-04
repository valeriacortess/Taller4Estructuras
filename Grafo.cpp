#include "Grafo.h"
using namespace std;

Grafo::Grafo() : n(0) {}

void Grafo::construir(const Universo& u) {
    n = u.cantidadPlanetas();
    matriz.assign(n, vector<Arista>(n, Arista{0.0, 0.0, 0.0, false}));

    // Solo se recorre la mitad superior (j > i) y se copia a la celda simetrica
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            const Planeta& pi = u.obtenerPlaneta(i);
            const Planeta& pj = u.obtenerPlaneta(j);
            Arista a;
            a.distancia = pi.distanciaA(pj);
            a.gravitacional = 1.0 + u.obtenerLambda() *
                              ((pi.obtenerT() - 1.0) + (pj.obtenerT() - 1.0)) / 2.0;
            a.combustible = u.obtenerK() * a.distancia * a.gravitacional;
            a.peligrosa = pi.esPeligrosoCon(pj.obtenerNombre());
            matriz[i][j] = a;
            matriz[j][i] = a;
        }
    }
}

const Arista& Grafo::obtenerArista(int i, int j) const { return matriz[i][j]; }
double Grafo::obtenerCombustible(int i, int j) const { return matriz[i][j].combustible; }
bool Grafo::esPeligrosa(int i, int j) const { return matriz[i][j].peligrosa; }
int Grafo::cantidadNodos() const { return n; }