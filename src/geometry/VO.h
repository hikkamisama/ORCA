#pragma once
#include "vec.h"
#include "circle.h"
#include "../const.h"

class VO {
public:
    VO() = default;
    VO(vec v1, vec v2, circle c2) : cas1(v1) ,cas2(v2), c1(c2) {}
    vec get_cas1() const;
    vec get_cas2() const;
    circle get_c1() const;
private:
    vec cas1, cas2;
    circle c1;
};