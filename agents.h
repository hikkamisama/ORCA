#pragma once

#include <iostream>
#include "circle.h"

struct agent {
    double r;
    double v_max;
};

std::ostream& operator<<(std::ostream& os, const agent& a) {
    os << "AGENT: with thiccness: " << a.r << " with v_max: " << a.v_max;
    return os;
}

std::istream& operator>>(std::istream& is, agent& a) {
    is >> a.r >> a.v_max;
    return is;
}