#pragma once

struct vec {
    double x, y;
    vec() = default;
    vec(double x1, double y1) : x(x1), y(y1) {}
    vec(const vec& v1): x(v1.x), y(v1.y) {}
    double norm() const;
};

vec operator-(const vec& v1, const vec& v2) {
    return vec(v1.x  - v2.x, v1.y - v2.y);
}

vec operator+(const vec& v1, const vec& v2) {
    return vec(v1.x  + v2.x, v1.y + v2.y);
}

vec operator*(const vec& v1, const double d1) {
    return vec(v1.x * d1, v1.y * d1);
}

vec operator/(const vec& v1, const double d1) {
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