#pragma once

struct vec {
    double x, y;
    vec() = default;
    vec(double x1, double y1) : x(x1), y(y1) {}
    vec(const vec& v1): x(v1.x), y(v1.y) {}
    vec(const vec& a, const vec& b) : x(b.x - a.x), y(b.y - a.y) {}
    double norm() const;
};

vec operator-(const vec& v1, const vec& v2) {
    return vec(v1.x - v2.x, v1.y - v2.y);
}

vec operator+(const vec& v1, const vec& v2) {
    return vec(v1.x + v2.x, v1.y + v2.y);
}

template <class T>
vec operator*(const vec& v1, T d1) {
    return vec(v1.x * d1, v1.y * d1);
}

template <class T>
vec operator/(const vec& v1, T d1) {
    return vec(v1.x / d1, v1.y / d1);
}

double vec::norm() const {
    return std::sqrt(x * x + y * y);
}

vec normalize(const vec& v) {
    return v / v.norm();
}

std::ostream& operator<<(std::ostream& os, const vec& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}

std::istream& operator>>(std::istream& is, vec& v) {
    is >> v.x >> v.y;
    return is;
}

double mul_cos(const vec& a, const vec& b) {
    return a.x * b.x + a.y * b.y;
}

double mul_sin(const vec& a, const vec& b) {
    return a.x * b.y - a.y * b.x;
}