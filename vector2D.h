#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cmath>

struct Vector2D {
    double x;
    double y;

    Vector2D(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& otro) const {
        return Vector2D(x + otro.x, y + otro.y);
    }

    Vector2D operator-(const Vector2D& otro) const {
        return Vector2D(x - otro.x, y - otro.y);
    }

    Vector2D operator*(double escalar) const {
        return Vector2D(x * escalar, y * escalar);
    }

    double magnitud() const {
        return std::sqrt(x * x + y * y);
    }
};

#endif // VECTOR2D_H