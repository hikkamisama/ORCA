#pragma once
#include "vec.h"

struct circle {
    vec p;
    double r;
    circle() = default;
    circle(double x1, double y1, double r1) : p(x1, y1), r(r1) {}
    circle(const vec& p1, double r1) : p(p1), r(r1) {}
};

std::ostream& operator<<(std::ostream& os, const circle& c) {
    os << "circle at: " << c.p << " with radius: " << c.r;
    return os;
}

std::istream& operator>>(std::istream& is, circle& c) {
    is >> c.p >> c.r;
    return is;
}