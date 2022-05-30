#include "vec.h"

double vec::get_x() const {
    return x;
}

double vec::get_y() const {
    return y;
}

vec operator-(const vec& v1, const vec& v2) {
    return vec(v1.get_x() - v2.get_x(), v1.get_y() - v2.get_y());
}

vec operator+(const vec& v1, const vec& v2) {
    return vec(v1.get_x() + v2.get_x(), v1.get_y() + v2.get_y());
}

template <class T>
vec operator*(const vec& v1, T d1) {
    return vec(v1.get_x() * d1, v1.get_y() * d1);
}

template <class T>
vec operator/(const vec& v1, T d1) {
    return vec(v1.get_x() / d1, v1.get_y() / d1);
}

double vec::norm() const {
    return std::sqrt(x * x + y * y);
}

vec normalize(const vec& v) {
    return v / v.norm();
}

std::ostream& operator<<(std::ostream& os, const vec& v) {
    os << "(" << v.get_x() << ", " << v.get_y() << ")";
    return os;
}

std::istream& operator>>(std::istream& is, vec& v) {
    is >> v.x >> v.y;
    return is;
}

double mul_cos(const vec& a, const vec& b) {
    return a.get_x() * b.get_x() + a.get_y() * b.get_y();
}

double mul_sin(const vec& a, const vec& b) {
    return a.get_x() * b.get_y() - a.get_y() * b.get_x();
}