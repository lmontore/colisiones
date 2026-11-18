#include "obstaculo.h"
#include <algorithm>
#include <cmath>

Obstaculo::Obstaculo(int id, Vector2D centro, double lado, double coefRestitucion)
    : id(id), centro(centro), lado(lado), coefRestitucion(coefRestitucion) {}

int Obstaculo::getId() const { return id; }
Vector2D Obstaculo::getCentro() const { return centro; }
double Obstaculo::getLado() const { return lado; }

bool Obstaculo::resolverColision(Particula& p, std::string& caraImpacto) const {
    if (!p.estaActiva()) return false;

    double mitad = lado / 2.0;
    double minX = centro.x - mitad, maxX = centro.x + mitad;
    double minY = centro.y - mitad, maxY = centro.y + mitad;

    Vector2D pos = p.getPosicion();
    Vector2D vel = p.getVelocidad();
    double radio = p.getRadio();

    double cercanoX = std::max(minX, std::min(pos.x, maxX));
    double cercanoY = std::max(minY, std::min(pos.y, maxY));

    double dx = pos.x - cercanoX;
    double dy = pos.y - cercanoY;
    double distSq = dx * dx + dy * dy;

    if (distSq < radio * radio) {
        double dist = std::sqrt(distSq);
        double penetracion = radio - dist;

        if (std::abs(dx) > std::abs(dy)) {
            if (dx > 0) {
                caraImpacto = "Derecha";
                pos.x += penetracion;
            } else {
                caraImpacto = "Izquierda";
                pos.x -= penetracion;
            }
            vel.x = -coefRestitucion * vel.x;
        } else {
            if (dy > 0) {
                caraImpacto = "Superior";
                pos.y += penetracion;
            } else {
                caraImpacto = "Inferior";
                pos.y -= penetracion;
            }
            vel.y = -coefRestitucion * vel.y;
        }

        p.setPosicion(pos);
        p.setVelocidad(vel);
        return true;
    }
    return false;
}