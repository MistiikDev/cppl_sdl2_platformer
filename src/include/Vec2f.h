#ifndef VEC2F_H
#define VEC2F_H

#include <iostream>
#include <math.h>

float LerpFloat(double a, double b, float t) {
    return a + (b - a) * t;
}

class Vec2f {
    public:
        Vec2f(double x, double y): x(x), y(y) {};    

        void print() {
            std::cout << "X: " << x << " / Y: " << y << '\n';
        }

        // Vector 2 basic vector accessers
        Vec2f Unit() {
            return Vec2f(this->x / this->Magnitude(), this->y / this->Magnitude());
        }

        double Magnitude() {
            return sqrt(this->x * this->x + this->y * this->y);
        }
        
        double Dot(const Vec2f& rhs) const {
            return this->x * rhs.x + this->y * rhs.y;
        }

        double Angle(Vec2f& rhs) {
            return acos(this->Dot(rhs) / (this->Magnitude() * rhs.Magnitude()));
        }

        Vec2f Lerp(const Vec2f& rhs, float alpha) const {
            return Vec2f(LerpFloat(this->x, rhs.x, alpha), LerpFloat(this->y, rhs.y, alpha));
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

        static const Vec2f zero;
        static const Vec2f one;

        double x, y;
};

const Vec2f Vec2f::zero = Vec2f(0.0, 0.0);
const Vec2f Vec2f::one  = Vec2f(1.0, 1.0);

#endif