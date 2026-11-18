#ifndef OBSTACULO_H
#define OBSTACULO_H

#include <string>
#include "vector2D.h"
#include "particulas.h"

class Obstaculo {
private:
    int id;
    Vector2D centro;
    double lado;
    double coefRestitucion;

public:
    Obstaculo(int id, Vector2D centro, double lado, double coefRestitucion);

    int getId() const;
    Vector2D getCentro() const;
    double getLado() const;

    bool resolverColision(Particula& p, std::string& caraImpacto) const;
};

#endif // OBSTACULO_H
