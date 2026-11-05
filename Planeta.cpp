#include "Planeta.h"
#include <cmath>
using namespace std;

Planeta::Planeta(const string& nombre, double x, double y, double z, double t)
    : nombre(nombre), x(x), y(y), z(z), t(t) {}

const string& Planeta::obtenerNombre() const { return nombre; }
double Planeta::obtenerX() const { return x; }
double Planeta::obtenerY() const { return y; }
double Planeta::obtenerZ() const { return z; }
double Planeta::obtenerT() const { return t; }
const vector<string>& Planeta::obtenerPeligrosos() const { return peligrosos; }

void Planeta::agregarPeligroso(const string& destino) {
    peligrosos.push_back(destino);
}

bool Planeta::esPeligrosoCon(const string& planetica) const {
    for (const string& p : peligrosos) {
        if (p == planetica) return true;
    }
    return false;
}

double Planeta::distanciaA(const Planeta& planetica) const {
    double dx = x - planetica.x;
    double dy = y - planetica.y;
    double dz = z - planetica.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}
