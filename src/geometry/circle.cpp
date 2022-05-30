#pragma once
#include "circle.h"

std::ostream& operator<<(std::ostream& os, const circle& c) {
    os << "circle at: " << c.p << " with radius: " << c.r;
    return os;
}

std::istream& operator>>(std::istream& is, circle& c) {
    is >> c.p >> c.r;
    return is;
}

vec circle::get_p() const {
    return p;
}

double circle::get_r() const {
    return r;
}