#ifndef VEC2F_H
#define VEC2F_H

#include <iostream>
#include <math.h>

class Vec2f {
    public:
        Vec2f(double x, double y): x(x), y(y) {};    

        void print() {
            std::cout << "X: " << x << " / Y: " << y << '\n';
        }

        // Vector 2 basic vector accessers
        Vec2f Unit(Vec2f& vector) {
            return Vec2f(vector.x / vector.Magnitude(), vector.y / vector.Magnitude());
        }

        double Magnitude() {
            return sqrt(x * x + y * y);
        }

        // Vector 2 operation overloading.

        Vec2f operator+(const Vec2f rhs) const {
            return Vec2f(this->x + rhs.x, this->y + rhs.y);
        }

        Vec2f operator-(const Vec2f rhs) const {
            return Vec2f(this->x - rhs.x, this->y - rhs.y);
        }

        // Scalar and vector product
        Vec2f operator*(const double scalar) const {
            return Vec2f(this->x * scalar, this->y * scalar);
        }

        Vec2f operator*(const Vec2f rhs) const {
            return Vec2f(this->x * rhs.x, this->y * rhs.y);
        }

        // Scalar and cector division
        Vec2f operator/(const double scalar) const {
            return Vec2f(this->x / scalar, this->y / scalar);
        }

        Vec2f operator/(const Vec2f rhs) const {
            return Vec2f(this->x / rhs.x, this->y / rhs.y);
        }

        // Equality
        bool operator==(const Vec2f& rhs) const {
            return x == rhs.x && y == rhs.y;
        }

        double x, y;
};

#endif