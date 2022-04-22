#pragma once
#include "vec.h"
#include <iostream>
#include <utility>
#include <tuple>

struct line {
    double a, b, c;

    line() = default;
    line (double a, double b, double c) : a(a), b(b), c(c) {};
    line(const vec& A, const vec& B) {
        a = B.y - A.y;
        b = A.x - B.x;
        c = A.y * (B.x - A.x) - A.x * (B.y - A.y);
    }
    double tan_line() const;
    std::tuple<double, double, double> get() const;
    double into(const vec& d) const;
};

std::istream& operator>>(std::istream& is, line& l) {
    is >> l.a >> l.b >> l.c;
    return is;
}

std::ostream& operator<<(std::ostream& os, line& l) {
    os << l.a << " " << l.b << " " << l.c;
    return os;
}

double line::tan_line() const {
    return -a / b;
}

bool operator<(const line& l1, const line& l2) {
    return l1.tan_line() < l2.tan_line();
}

bool operator>(const line& l1, const line& l2) {
    return l1.tan_line() > l2.tan_line();
}

std::tuple<double, double, double> line::get() const {
    return std::tie(a, b, c);
}

bool intercept(const line& l1, const line& l2) {
    auto [a1, b1, c1] = l1.get();
    auto [a2, b2, c2] = l2.get();
    return (a1 * b2 != b1 * a2);
}

bool parallel(const line& l1, const line& l2) {
    auto [a1, b1, c1] = l1.get();
    auto [a2, b2, c2] = l2.get();
    return (a1 * b2 == b1 * a2) && (a1 * c2 != c1 * a2);
}

bool equal(const line& l1, const line& l2) {
    auto [a1, b1, c1] = l1.get();
    auto [a2, b2, c2] = l2.get();
    return (a1 * b2 == b1 * a2) && (a1 / a2 == c1 / c2);
}

vec interception(const line& l1, const line& l2) {
    double x = - ((l1.c * l2.b - l2.c * l1.b) / (l1.a * l2.b - l2.a * l1.b));
    double y = - ((l1.a * l2.c - l2.a * l1.c) /(l1.a * l2.b - l2.a * l1.b));
    return vec(x, y);
}

double line::into(const vec& d) const {
    return a * d.x + b * d.y + c;
}

double det(const line& l1, const line& l2, const line& l3) {
    auto [a1, b1, c1] = l1.get();
    auto [a2, b2, c2] = l2.get();
    auto [a3, b3, c3] = l3.get();
    double det = a1 * b2 * c3 + a3 * b1 * c2 + a2 * b3 * c1;
    det -= a3 * b2 * c1 + a2 * b1 * c3 + a1 * b3 * c2;
    return det;
}