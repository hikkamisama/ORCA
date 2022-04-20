#pragma once

#include "dot.h"
#include "vec.h"
#include "line.h"
#include "VO.h"

std::vector<dot> convex_hull(std::vector<line>& lines) {
    std::vector<dot> dots;
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = i + 1; j < lines.size(); ++j) {
            if (intercept(lines[i], lines[j])) {
                dot t = interception(lines[i], lines[j]);
                bool flag = false;
                for (int k = 0; k < lines.size(); ++k) {
                    if (lines[k].into(t) < -eps) {
                        flag = true;
                        break;
                    }
                }
                if (!flag) {
                    dots.push_back(t);
                }
            }
        }
    }
    return dots;
}

double dot_to_conv(const dot& c1, const dot& c2, const dot& d) {
    line l1(c1, c2);
    auto [a, b, c] = l1.get();
    vec c1c2(c1, c2);
    vec c2c1(c2, c1);
    vec c1d(c1, d);
    vec c2d(c2, d);
    if (mul_cos(c1c2, c1d) < 0) {
        return vec(d, c1).norm();
    }
    if (mul_cos(c2c1, c2d) < 0) {
        return vec(d, c2).norm();
    }
    return std::abs(a * d.x + b * d.y + c) / std::sqrt(a * a + b * b);
}

double solve(std::vector<dot> hull, dot v) {
    double argmin = -1;
    for (int i = 0; i < hull.size(); ++i) {
        for (int j = i + 1; j < hull.size(); ++j) {
            double curr = dot_to_conv(hull[i], hull[j], v);
            if (argmin == -1 || curr < argmin) {
                argmin = curr;
            }
        }
    }
    return argmin;
}