#include "simulador.h"

Simulador::Simulador(double anchoCaja, double altoCaja, double dt)
    : anchoCaja(anchoCaja), altoCaja(altoCaja), dt(dt), tiempoActual(0.0) {
    archivoTrayectorias.open("trayectorias.txt");
    archivoColisiones.open("colisiones.txt");

    archivoTrayectorias << "t\tid\tx\ty\tvx\tvy\tradio\tactiva\n";
    archivoColisiones << "t\ttipo\tdetalle\tx\ty\n";
}

Simulador::~Simulador() {
    if (archivoTrayectorias.is_open()) archivoTrayectorias.close();
    if (archivoColisiones.is_open()) archivoColisiones.close();
}

void Simulador::agregarParticula(const Particula& p) {
    particulas.push_back(p);
}

void Simulador::agregarObstaculo(const Obstaculo& o) {
    obstaculos.push_back(o);
}

void Simulador::verificarColisionesParedes() {
    for (auto& p : particulas) {
        if (!p.estaActiva()) continue;

        Vector2D pos = p.getPosicion();
        Vector2D vel = p.getVelocidad();
        double r = p.getRadio();

        if (pos.x - r <= 0.0) {
            pos.x = r;
            vel.x = -vel.x;
            archivoColisiones << tiempoActual << "\tPared\tP" << p.getId() << "_Izquierda\t" << pos.x << "\t" << pos.y << "\n";
        } else if (pos.x + r >= anchoCaja) {
            pos.x = anchoCaja - r;
            vel.x = -vel.x;
            archivoColisiones << tiempoActual << "\tPared\tP" << p.getId() << "_Derecha\t" << pos.x << "\t" << pos.y << "\n";
        }

        if (pos.y - r <= 0.0) {
            pos.y = r;
            vel.y = -vel.y;
            archivoColisiones << tiempoActual << "\tPared\tP" << p.getId() << "_Inferior\t" << pos.x << "\t" << pos.y << "\n";
        } else if (pos.y + r >= altoCaja) {
            pos.y = altoCaja - r;
            vel.y = -vel.y;
            archivoColisiones << tiempoActual << "\tPared\tP" << p.getId() << "_Superior\t" << pos.x << "\t" << pos.y << "\n";
        }

        p.setPosicion(pos);
        p.setVelocidad(vel);
    }
}

void Simulador::verificarColisionesObstaculos() {
    for (auto& p : particulas) {
        if (!p.estaActiva()) continue;
        for (const auto& obs : obstaculos) {
            std::string cara;
            if (obs.resolverColision(p, cara)) {
                Vector2D pos = p.getPosicion();
                archivoColisiones << tiempoActual << "\tObstaculo\tP" << p.getId() << "_Obs" << obs.getId() << "_" << cara
                                  << "\t" << pos.x << "\t" << pos.y << "\n";
            }
        }
    }
}

void Simulador::verificarColisionesParticulas() {
    for (size_t i = 0; i < particulas.size(); ++i) {
        if (!particulas[i].estaActiva()) continue;
        for (size_t j = i + 1; j < particulas.size(); ++j) {
            if (!particulas[j].estaActiva()) continue;

            Vector2D diff = particulas[i].getPosicion() - particulas[j].getPosicion();
            double sumaRadios = particulas[i].getRadio() + particulas[j].getRadio();

            if (diff.magnitud() <= sumaRadios) {
                Vector2D pos = particulas[i].getPosicion();
                archivoColisiones << tiempoActual << "\tFusion\tP" << particulas[i].getId() << "+P" << particulas[j].getId()
                                  << "\t" << pos.x << "\t" << pos.y << "\n";
                particulas[i].fusionarCon(particulas[j]);
            }
        }
    }
}

void Simulador::registrarEstado() {
    for (const auto& p : particulas) {
        Vector2D pos = p.getPosicion();
        Vector2D vel = p.getVelocidad();
        archivoTrayectorias << tiempoActual << "\t" << p.getId() << "\t"
                            << pos.x << "\t" << pos.y << "\t"
                            << vel.x << "\t" << vel.y << "\t"
                            << p.getRadio() << "\t" << p.estaActiva() << "\n";
    }
}

void Simulador::ejecutar(double tiempoTotal) {
    registrarEstado();
    while (tiempoActual < tiempoTotal) {
        for (auto& p : particulas) {
            p.mover(dt);
        }
        tiempoActual += dt;

        verificarColisionesParedes();
        verificarColisionesObstaculos();
        verificarColisionesParticulas();
        registrarEstado();
    }
}