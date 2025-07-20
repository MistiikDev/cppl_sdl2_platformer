#ifndef VEC2F_H
#define VEC2F_H

#include <iostream>
#include <math.h>
#include "MathUtil.h"


class Vec2f
{
public:
    static const Vec2f zero;
    static const Vec2f one;

    Vec2f() : x(0.0), y(0.0) {}
    Vec2f(double x, double y) : x(x), y(y) {};

    void print()
    {
        std::cout << "X: " << x << " / Y: " << y << '\n';
    }

    // Vector 2 basic vector accessers
    Vec2f Unit() {
        if (x == 0 || y == 0){
            return Vec2f(x, y);
        }

        return Vec2f(this->x / this->Magnitude(), this->y / this->Magnitude());
    }

    Vec2f Lerp(const Vec2f &rhs, float alpha) const {
        return Vec2f(MathUtil::LerpFloat(this->x, rhs.x, alpha), MathUtil::LerpFloat(this->y, rhs.y, alpha));
    }

    // Vector 2 operation overloading.
    Vec2f operator+(const Vec2f rhs) const { return Vec2f(this->x + rhs.x, this->y + rhs.y); }
    Vec2f operator-(const Vec2f rhs) const { return Vec2f(this->x - rhs.x, this->y - rhs.y); }

    // Scalar and vector product
    Vec2f operator*(const double scalar) const { return Vec2f(this->x * scalar, this->y * scalar); }
    Vec2f operator*(const Vec2f rhs) const { return Vec2f(this->x * rhs.x, this->y * rhs.y); }

    // Scalar and cector division
    Vec2f operator/(const double scalar) const { return Vec2f(this->x / scalar, this->y / scalar); }
    Vec2f operator/(const Vec2f rhs) const { return Vec2f(this->x / rhs.x, this->y / rhs.y); }

    // Equality
    bool operator==(const Vec2f &rhs) const { return x == rhs.x && y == rhs.y; }

    double x, y;

    double Magnitude() {
        return sqrt(this->x * this->x + this->y * this->y);
    }

    double Dot(const Vec2f &rhs) const {
        return this->x * rhs.x + this->y * rhs.y;
    }

    double Angle(Vec2f &rhs) {
        return acos(this->Dot(rhs) / (this->Magnitude() * rhs.Magnitude()));
    }
};

#endif