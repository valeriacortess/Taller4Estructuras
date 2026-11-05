#include "Mision.h"
#include <fstream>
#include <iomanip>
using namespace std;

Mision::Mision(const Universo& universo, const Grafo& grafo)
  : universo(universo), grafo(grafo){}

const vector<Desplazamiento>& Mision::obtenerDesplazamientos() const{
    return desplazamientos;
}

void Mision::registrar(int origen, int destino){
    const Arista& a = grafo.obtenerArista(origen, destino);
    double acumulado = a.combustible;
      if (!desplazamientos.empty()){
        acumulado = desplazamientos.back().obtenerAcumulado() + a.combustible;
    }
  int numero = desplazamientos.size + 1;
  desplazamientos.push_back(Desplazamiento(numero, Universo.obtenerPlaneta(origen).obtenerNombre(), Universo.obtenerPlaneta(destino).obtenerNombre(), a.distancia, a.gravitacional, a.combustible, a.peligrosa, acumulado));
  recorrido.push_back(destino);
}

void Mision::ejecutar(){
  desplazamientos.clear();
  recorrido.clear();

  int n = grafo.cantidadNodos();
  int tierra = Universo.obtenerIndice("Tierra");

  vector<bool> visitado(n, false);
  visitado[tierra] = true;
  recorrido.push_back(tierra);

  int actual = tierra;
  int pendientes = n - 1;

  while (pendientes > 0) {
      int mejorSegura = -1;
      int mejorPeligrosa = -1;

      for (int i = 0; i < n; i++) {
        if(visitado[i]) continue;
        double costo = grafo.obtenerCombustible (actual, i);

        if (grafo.esPeligrosa(actual, i)) {
        if (mejorPeligrosa == -1 || costo < grafo.obtenerCombustible(actual, mejorPeligrosa)){
                    mejorPeligrosa = i;
        }
      } else {
        if (mejorSegura == -1 || costo < grafo.obtenerCombustible (actual, mejorSegura)){
        mejorSegura = i;
        }
      }
    }
    int siguiente;
    if (mejorSegura != -1){
      siguiente = mejorSegura;
    } else{
      siguiente = mejorPeligrosa;
    }

    registrar(actual, siguiente);
    visitado[siguiente] = true;
    pendientes--;
    actual = siguiente;
  }
  registrar (actual, tierra);
}

bool Mision::escribirDetalle(const string& nombreArchivo) const {
    ofstream out(nombreArchivo);
    if (!out) return false;
    out << fixed << setprecision(2);
    out << "MISION LAZARO - DETALLE DEL RECORRIDO\n\n";
    for (const Desplazamiento& d : desplazamientos) {
        out << "Desplazamiento " << d.obtenerNumero() << "\n";
        out << "Origen: " << d.obtenerOrigen() << "\n";
        out << "Destino: " << d.obtenerDestino() << "\n";
        out << "Distancia: " << d.obtenerDistancia() << "\n";
        out << "Factor gravitacional: " << d.obtenerFactorG() << "\n";
        out << "Combustible consumido: " << d.obtenerCombustible() << "\n";
        if (d.esPeligroso()) {
            out << "Tipo de conexion: Peligrosa\n";
        } else {
            out << "Tipo de conexion: Segura\n";
        }
        out << "Combustible acumulado: " << d.obtenerAcumulado() << "\n\n";
    }
    return true;
}

bool Mision::escribirResumen(const string& nombreArchivo) const {
    ofstream out(nombreArchivo);
    if (!out) return false;
    out << fixed << setprecision(2);
 
    double distanciaTotal = 0;
    double combustibleTotal = 0;
    int seguras = 0;
    int peligrosas = 0;
    int idxMayor = 0;
    int idxMenor = 0;
 
    for (int i = 0; i < (int)desplazamientos.size(); i++) {
        const Desplazamiento& d = desplazamientos[i];
        distanciaTotal += d.obtenerDistancia();
        combustibleTotal += d.obtenerCombustible();
        if (d.esPeligroso()) {
            peligrosas++;
        } else {
            seguras++;
        }
        if (d.obtenerCombustible() > desplazamientos[idxMayor].obtenerCombustible()) idxMayor = i;
        if (d.obtenerCombustible() < desplazamientos[idxMenor].obtenerCombustible()) idxMenor = i;
    }

int m = universo.cantidadPlanetas();
    out << "MISION LAZARO - RESUMEN\n\n";
    out << "Planetas registrados: " << m << "\n";
    out << "Planetas explorados: " << (m - 1) << "\n";
 
    out << "Recorrido:\n";
    for (int i = 0; i < (int)recorrido.size(); i++) {
        if (i > 0) out << " -> ";
        out << universo.obtenerPlaneta(recorrido[i]).obtenerNombre();
    }
    out << "\n\n";
    out << "Desplazamientos realizados: " << desplazamientos.size() << "\n";
    out << "Distancia total: " << distanciaTotal << "\n";
    out << "Combustible total: " << combustibleTotal << "\n";
    out << "Conexiones seguras utilizadas: " << seguras << "\n";
    out << "Conexiones peligrosas utilizadas: " << peligrosas << "\n\n";
    out << "Mayor consumo:\n" << desplazamientos[idxMayor].obtenerOrigen()
        << " -> " << desplazamientos[idxMayor].obtenerDestino() << "\n";
    out << "Menor consumo:\n" << desplazamientos[idxMenor].obtenerOrigen()
        << " -> " << desplazamientos[idxMenor].obtenerDestino() << "\n\n";
    out << "Estado de la mision: COMPLETADA\n";
    out << "Regreso a la Tierra: SI\n";
    return true;
}
    
