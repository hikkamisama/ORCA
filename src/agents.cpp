#pragma once

#include "agents.h"

std::ostream& operator<<(std::ostream& os, const agent& a) {
    os << "AGENT №" << a.num << ": with radius: " << a.r << " with v_max: " << a.v_max;
    return os;
}

std::istream& operator>>(std::istream& is, agent& a) {
    is >> a.num >> a.r >> a.v_max;
    a.r *= buff;
    return is;
}

int agent::get_num() const {
    return num;
}

double agent::get_r() const {
    return r;
}

double agent::get_v_max() const {
    return v_max;
}