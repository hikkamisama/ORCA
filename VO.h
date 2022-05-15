#pragma once
#include "vec.h"
#include "circle.h"

struct VO {
    vec cas1, cas2;
    circle c1;
    VO() = default;
    VO(vec v1, vec v2, circle c2) : cas1(v1) ,cas2(v2), c1(c2) {}
};

VO find_cas(circle c, vec p) {
    double px = c.p.x - p.x;
    double py = c.p.y - p.y;
    double r = c.r;
    double d = std::sqrt(px * px + py * py);
    double r2 = std::sqrt(std::max(d * d - r * r, 0.));
    double v = ((r2 * r2 - r * r) / d - d) / 2;
    double h = std::sqrt(std::max(r * r - v * v, 0.));
    vec o2o1(px, py);
    o2o1 = normalize(o2o1);
    vec ort0201(o2o1.y, -o2o1.x);
    o2o1 = o2o1 * v;
    ort0201 = ort0201 * h;
    vec ans1 = c.p + o2o1 + ort0201;
    vec ans2 = c.p + o2o1 - ort0201;

    return VO(ans1, ans2, c);

}