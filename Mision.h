#ifndef MISION_H
#define MISION_H

#include <vector>
#include <string>
#include "Desplazamiento.h" 
#include "Grafo.h"
#include "Universo.h"
using namespace std;

class Mision {
private:
  const Universo& universo;
  const Grafo& grafo;
  vector<Desplazamiento> desplazamientos;
  vector<int> recorrido;

void registrar(int origen, int destino); 

public:
  Mision(const Universo& universo, const Grafo& grafo);

  void ejecutar();

const vector<Desplazamiento>& obtenerDesplazamientos() const;

bool escribirDetalle (const string& nombreArchivo) const;
bool escribirResumen (const string& nombreArchivo) const;
};

#endif
