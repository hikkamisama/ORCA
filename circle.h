#pragma once
#include "vec.h"

struct circle {
    vec p;
    double r;
    circle() = default;
    circle(double x1, double y1, double r1) : p(x1, y1), r(r1) {}
    circle(vec p1, double r1) : p(p1), r(r1) {}
};