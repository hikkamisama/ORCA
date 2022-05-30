#pragma once
#include "../const.h"
#include "vec.h"
#include <iostream>
#include <utility>
#include <tuple>

class line {
public:
    line() = default;
    line (double a, double b, double c) : a(a), b(b), c(c) {};
    line(const vec& A, const vec& B) {
        a = B.get_y() - A.get_y();
        b = A.get_x() - B.get_x();
        c = A.get_y() * (B.get_x() - A.get_x()) - A.get_x() * (B.get_y() - A.get_y());
    }
    friend std::ostream& operator<<(std::ostream& os, const line& l);
    friend std::istream& operator>>(std::istream& is, line& l);
    double tan_line() const;
    std::tuple<double, double, double> get() const;
    double into(const vec& d) const;
    double get_a() const;
    double get_b() const;
    double get_c() const;
private:
    double a, b, c;
};