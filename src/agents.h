#pragma once

#include <iostream>
#include "const.h"

class agent {
public:
    agent() = default;
    agent(int num, double r, double v_max) : num(num), r(r * buff), v_max(v_max) {}
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