#ifndef SIMULADOR_H
#define SIMULADOR_H

#include <vector>
#include <fstream>
#include <string>
#include "particulas.h"
#include "obstaculo.h"

class Simulador {
private:
    double anchoCaja;
    double altoCaja;
    double dt;
    double tiempoActual;
    std::vector<Particula> particulas;
    std::vector<Obstaculo> obstaculos;
    std::ofstream archivoTrayectorias;
    std::ofstream archivoColisiones;

    void verificarColisionesParedes();
    void verificarColisionesObstaculos();
    void verificarColisionesParticulas();
    void registrarEstado();

public:
    Simulador(double anchoCaja, double altoCaja, double dt);
    ~Simulador();

    void agregarParticula(const Particula& p);
    void agregarObstaculo(const Obstaculo& o);
    void ejecutar(double tiempoTotal);
};

#endif // SIMULADOR_H