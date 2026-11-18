#include "particulas.h"
#include <cmath>

Particula::Particula(int id, double masa, double radio, Vector2D posicion, Vector2D velocidad)
    : id(id), masa(masa), radio(radio), posicion(posicion), velocidad(velocidad), activa(true) {}

int Particula::getId() const { return id; }
double Particula::getMasa() const { return masa; }
double Particula::getRadio() const { return radio; }
Vector2D Particula::getPosicion() const { return posicion; }
Vector2D Particula::getVelocidad() const { return velocidad; }
bool Particula::estaActiva() const { return activa; }

void Particula::setPosicion(const Vector2D& nuevaPos) { posicion = nuevaPos; }
void Particula::setVelocidad(const Vector2D& nuevaVel) { velocidad = nuevaVel; }
void Particula::desactivar() { activa = false; }

void Particula::mover(double dt) {
    if (!activa) return;
    posicion = posicion + velocidad * dt;
}

void Particula::fusionarCon(Particula& otra) {
    double masaTotal = masa + otra.masa;
    posicion = (posicion * masa + otra.posicion * otra.masa) * (1.0 / masaTotal);
    velocidad = (velocidad * masa + otra.velocidad * otra.masa) * (1.0 / masaTotal);
    radio = std::sqrt(radio * radio + otra.radio * otra.radio);
    masa = masaTotal;
    otra.desactivar();
}