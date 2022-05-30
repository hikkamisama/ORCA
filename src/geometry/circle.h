#pragma once
#include "../const.h"
#include "vec.h"
#include <iostream>

class circle {
public:
    circle() = default;
    circle(double x1, double y1, double r1) : p(x1, y1), r(r1) {}
    circle(vec p1, double r1) : p(p1), r(r1) {}
    friend std::ostream& operator<<(std::ostream& os, const circle& c);
    friend std::istream& operator>>(std::istream& is, circle& c);
    vec get_p() const;
    double get_r() const;
private:
    vec p;
    double r;
};