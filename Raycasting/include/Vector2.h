#pragma once

#include <tuple>
#include <ostream>

template <typename T>
struct Vector2 {
    T x;
    T y;

    Vector2 operator -() const {
        return {-x, -y};
    }

    Vector2 operator +(const Vector2 other) const {
        return {x + other.x, y + other.y};
    }

    Vector2 operator -(const Vector2 other) const {
        return (*this) + (-other);
    }

    T operator *(const Vector2 other) const {
        return (x * other.x) + (y * other.y);
    }

    Vector2<T> operator *(const T scalar) const {
        return {x * scalar, y * scalar};
    }

    void normalize() {
        double length = this->length();
        x = static_cast<T>(static_cast<double>(x) / length);
        y = static_cast<T>(static_cast<double>(y) / length);
    }

    void operator +=(const Vector2 other) {
        x += other.x;
        y += other.y;
    }

    void operator *=(const T scalar) {
        x *= scalar;
        y *= scalar;
    }

    double length() const {
        auto [xd, yd] = std::make_tuple(static_cast<double>(x), static_cast<double>(y));
        return sqrt((xd * xd) + (yd * yd));
    }

    float lengthf() const {
        auto [xf, yf] = std::make_tuple(static_cast<float>(x), static_cast<float>(y));
        return sqrtf((xf * xf) + (yf * yf));
    }

    friend std::ostream& operator << (std::ostream& out, Vector2 vec) {
        out << "(" << vec.x << ", " << vec.y << ")";
        return out;
    }
};

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<double> Vectur2d;
typedef Vector2<long> Vector2l;