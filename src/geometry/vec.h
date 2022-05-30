#pragma once
#include <iostream>
#include <cmath>
#include "../const.h"

class vec {
public:
    vec() = default;
    vec(double x1, double y1) : x(x1), y(y1) {}
    vec(const vec& v1): x(v1.x), y(v1.y) {}
    vec(const vec& a, const vec& b) : x(b.x - a.x), y(b.y - a.y) {}
    friend std::ostream& operator<<(std::ostream& os, const vec& v);
    friend std::istream& operator>>(std::istream& is, vec& v);
    double norm() const;
    double get_x() const;
    double get_y() const;
private:
    double x, y;
};