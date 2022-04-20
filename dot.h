#pragma once
#include <iostream>

struct dot {
    double x, y;
    dot() = default;
    dot(double x1, double y1) : x(x1), y(y1) {}
};

bool operator==(const dot& a, const dot& b) {
    return (a.x == b.x && a.y == b.y);
}

bool operator<(const dot& a, const dot& b) {
    if (a.x != b.x) {
        return a.x < b.x;
    } else {
        return a.y < b.y;
    }
}

bool operator>(const dot& a, const dot& b) {
    if (a.x != b.x) {
        return a.x > b.x;
    } else {
        return a.y > b.y;
    }
}

std::istream& operator>>(std::istream& is, dot& a) {
    is >> a.x >> a.y;
    return is;
}

std::ostream& operator<<(std::ostream& os, dot& a) {
    os << a.x << " " << a.y;
    return os;
}
