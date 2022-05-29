#pragma once

#include <iostream>

extern double buff = 1.3;

class agent {
public:
    agent(int num, double r, double v_max) : num(num), r(r * buff), v_max(v_max) {}
    agent() = default;
    friend std::ostream& operator<<(std::ostream& os, const agent& a);
    friend std::istream& operator>>(std::istream& is, agent& a);
    int get_num() const;
    double get_r() const;
    double get_v_max() const;
private:
    int num;
    double r;
    double v_max;
};

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