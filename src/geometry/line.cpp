#include "line.h"

double line::get_a() const {
    return a;
}

double line::get_b() const {
    return b;
}

double line::get_c() const {
    return c;
}

std::istream& operator>>(std::istream& is, line& l) {
    is >> l.a >> l.b >> l.c;
    return is;
}

std::ostream& operator<<(std::ostream& os, const line& l) {
    os << l.a << "x +" << l.b << "y +" << l.c;
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
    auto [a1, b1, c1] = l1.get();
    auto [a2, b2, c2] = l2.get();
    double x = - ((c1 * b2 - c2 * b1) / (a1 * b2 - a2 * b1));
    double y = - ((a1 * c2 - a2 * c1) /(a1 * b2 - a2 * b1));
    return vec(x, y);
}

double line::into(const vec& d) const {
    return a * d.get_x() + b * d.get_y() + c;
}

double det(const line& l1, const line& l2, const line& l3) {
    auto [a1, b1, c1] = l1.get();
    auto [a2, b2, c2] = l2.get();
    auto [a3, b3, c3] = l3.get();
    double det = a1 * b2 * c3 + a3 * b1 * c2 + a2 * b3 * c1;
    det -= a3 * b2 * c1 + a2 * b1 * c3 + a1 * b3 * c2;
    return det;
}