#ifndef PARTICULAS_H
#define PARTICULAS_H

#include "vector2D.h"

class Particula {
private:
    int id;
    double masa;
    double radio;
    Vector2D posicion;
    Vector2D velocidad;
    bool activa;

public:
    Particula(int id, double masa, double radio, Vector2D posicion, Vector2D velocidad);

    int getId() const;
    double getMasa() const;
    double getRadio() const;
    Vector2D getPosicion() const;
    Vector2D getVelocidad() const;
    bool estaActiva() const;

    void setPosicion(const Vector2D& nuevaPos);
    void setVelocidad(const Vector2D& nuevaVel);
    void desactivar();

    void mover(double dt);
    void fusionarCon(Particula& otra);
};

#endif // PARTICULAS_H