#include "frame.h"

void frame::draw(const agent& a) const {
    int num = a.get_num();
    os 
    << "type AGENT" 
    << "; num " << num
    << "; x " << slv.get_currs()[num].get_x() 
    << "; y " << slv.get_currs()[num].get_y() 
    << "; r " << a.get_r() 
    << std::endl;
}

void frame::draw(const line& l, int i) {
    if (LOG) {
        vec d1(0, 0);
        vec d2(0, 1);
        vec d3(1, 0);
        d1 = d1 + proj_to_line(l, d1);
        d2 = d2 + proj_to_line(l, d2);
        d3 = d3 + proj_to_line(l, d3);
        vec dd1, dd2;
        if ((d1 - d2).norm() >= (d1 - d3).norm() && (d1 - d2).norm() >= (d2 - d3).norm()) {
            dd1 = d1;
            dd2 = d2;
        } else if ((d1 - d3).norm() >= (d2 - d3).norm()) {
            dd1 = d1;
            dd2 = d3;
        } else {
            dd1 = d2;
            dd2 = d3;
        }
        dd1 = dd1 + slv.get_currs()[i];
        dd2 = dd2 + slv.get_currs()[i];
        os << "type LINE" 
        << "; x1 " << dd1.get_x()
        << "; y1 " << dd1.get_y()
        << "; x2 " << dd2.get_x()
        << "; y2 " << dd2.get_y()
        << "; num " << i
        << std::endl;
    }
}

void frame::draw(const vec& v, int i) {
    os << "type VEC"
    << "; x " << v.get_x()
    << "; y " << v.get_y()
    << "; num " << i
    << std::endl;
}

void frame::draw(const std::vector<vec>& convex, int i) {
    if (LOG) {
        for (int j = 0; j < convex.size(); ++j) {
            draw(convex[j], i);
        }
    }
}