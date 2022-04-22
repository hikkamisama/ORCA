#pragma once

#include <cmath>
#include "vec.h"
#include "line.h"
#include "VO.h"

int sign(double a) {
    if (std::abs(a) < eps) {
        return 3;
    }
    if (a < 0) {
        return 2;
    }
    return 1;
}

bool inside_beams(const vec& v1, const vec& v2, const vec& to_check) {
    return sign(mul_sin(v1, v2)) & sign(mul_sin(v1, to_check)) & sign(mul_sin(to_check,v2));
}

vec proj_to_line(const line& l, const vec& v) {
    double d = l.into(v);
    return vec(-l.a * d, -l.b * d) / (l.a * l.a + l.b * l.b);
}

std::pair<bool, vec> dot_to_beam(const vec& v_beam, const vec& d_beam, const vec& d) {
    vec d_new = d - d_beam;
    if (mul_cos(v_beam, d_new) < eps) {
        return {true, d_beam - d};
    } else {
        return {false, proj_to_line(line(-v_beam.y, v_beam.x , 0), d_new)};
    }
}

std::vector<vec> convex_hull(std::vector<line>& lines) {
    std::vector<vec> dots;
    for (int i = 0; i < lines.size(); ++i) {
        for (int j = i + 1; j < lines.size(); ++j) {
            if (intercept(lines[i], lines[j])) {
                vec t = interception(lines[i], lines[j]);
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

vec dot_to_conv(const vec& c1, const vec& c2, const vec& d) {
    line l1(c1, c2);
    auto [a, b, c] = l1.get();
    vec c1c2(c1, c2);
    vec c2c1(c2, c1);
    vec c1d(c1, d);
    vec c2d(c2, d);
    if (mul_cos(c1c2, c1d) < 0) {
        return vec(d, c1);
    }
    if (mul_cos(c2c1, c2d) < 0) {
        return vec(d, c2);
    }
    return proj_to_line(line(c1, c2), d);
}

vec solve(std::vector<vec> hull, const vec& v) {
    double argmin = -1;
    vec ans;
    for (int i = 0; i < hull.size(); ++i) {
        for (int j = i + 1; j < hull.size(); ++j) {
            vec curr_vec = dot_to_conv(hull[i], hull[j], v);
            double curr = curr_vec.norm();
            if (argmin == -1 || curr < argmin) {
                argmin = curr;
                ans = curr_vec;
            }
        }
    }
    return v + ans;
}

std::pair<vec, vec> find_v_n(const VO& vobs, const vec& v) {
    vec u, n;
    auto [flag1, to_first] = dot_to_beam(vobs.cas1, vobs.c1.p, v);
    auto [flag2, to_second] = dot_to_beam(vobs.cas2, vobs.c1.p, v);
    if (flag1 && flag2) {
        u = normalize(v - vobs.c1.p) * vobs.c1.r + (vobs.c1.p - v);
    } else {
        vec need = vobs.cas2;
        if (to_first.norm() <= to_second.norm()) {
            need = vobs.cas1;
        }
        auto [flag3, to_vo] = dot_to_beam(need, vec(0, 0), v);
        u = to_vo;
    }
    n = normalize(u);
    if (!inside_beams(vobs.cas1, vobs.cas2, v - vobs.c1.p)) {
        vec p1(v + n);
        vec p2(v - n);
        if ((p1 - vobs.c1.p).norm() <= (p2 - vobs.c1.p).norm()) {
            n = n * (-1);
        }
    }
    return std::make_pair(u, n);
}

line struct_half_plane(const vec& v_opt, const vec& u, const vec& n) {
    return line(n.x, n.y, -mul_cos(v_opt + u / 2, n));
}

std::vector<line> poly_for_vmax(double v_max, int i_max) {
    double pie = acos(-1);
    std::vector<line> poly;
    for (int i = 1; i < i_max + 1; ++i) {
        vec A(std::cos(2 * pie / i_max * i), std::sin(2 * pie / i_max * i));
        vec B(std::cos(2 * pie / i_max * (i + 1)), std::sin(2 * pie / i_max * (i + 1)));
        A = A * v_max;
        B = B * v_max;
        line l(A, B);
        if (l.c < 0) {
            l = line(B, A);
        }
        poly.push_back(l);
    }
    return poly;
}