#include "Universo.h"
using namespace std;

Universo::Universo(double k, double lambda) : k(k), lambda(lambda) {}

void Universo::agregarPlaneta(const Planeta& p) {
    planetas.push_back(p);
}

double Universo::obtenerK() const { return k; }
double Universo::obtenerLambda() const { return lambda; }

int Universo::obtenerIndice(const string& nombre) const {
    for (int i = 0; i < (int)planetas.size(); i++) {
        if (planetas[i].obtenerNombre() == nombre) return i;
    }
    return -1;
}

const Planeta& Universo::obtenerPlaneta(int i) const { return planetas[i]; }
int Universo::cantidadPlanetas() const { return (int)planetas.size(); }

bool Universo::validar(string& mensaje) const {
    int m = (int)planetas.size();
    int cuentaTierra = 0;

    for (int i = 0; i < m; i++) {
        const Planeta& p = planetas[i];

        // Nombres unicos
        for (int j = i + 1; j < m; j++) {
            if (planetas[j].obtenerNombre() == p.obtenerNombre()) {
                mensaje = "Nombre de planeta repetido: " + p.obtenerNombre();
                return false;
            }
        }

        // Factor temporal >= 1
        if (p.obtenerT() < 1) {
            mensaje = "Factor temporal menor que 1 en el planeta " + p.obtenerNombre();
            return false;
        }

        if (p.obtenerNombre() == "Tierra") cuentaTierra++;

        // Conexiones peligrosas
        for (const string& destino : p.obtenerPeligrosos()) {
            if (destino == p.obtenerNombre()) {
                mensaje = "El planeta " + destino + " aparece en su propia lista de peligrosos";
                return false;
            }
            int idx = obtenerIndice(destino);
            if (idx == -1) {
                mensaje = "Conexion peligrosa hacia un planeta inexistente: " + destino;
                return false;
            }
            if (!planetas[idx].esPeligrosoCon(p.obtenerNombre())) {
                mensaje = "Conexion peligrosa no bidireccional: " + p.obtenerNombre() + " -> " + destino;
                return false;
            }
        }
    }

    if (cuentaTierra != 1) {
        mensaje = "Debe existir exactamente un planeta llamado Tierra";
        return false;
    }
    return true;
}