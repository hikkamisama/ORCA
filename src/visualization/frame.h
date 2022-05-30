#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "../agents.h"
#include "../geometry/geom.h"
#include "../algo.h"

class frame {
public:
    frame (const std::string& f_name, const Solver& slv) : fs(f_name, std::ios::out | std::ios::trunc), os(fs), slv(slv) {}
    void draw(const agent& a) const {
        int num = a.get_num();
        os 
        << "type AGENT" 
        << "; num " << num
        << "; x " << slv.get_currs()[num].get_x() 
        << "; y " << slv.get_currs()[num].get_y() 
        << "; r " << a.get_r() 
        << std::endl;
    }
    void draw(const end& e) {
        os << "type END" << std::endl;
    }
    void draw(const line& l, int i) {
        return;
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
    void draw(const vec& v, int i) {
        os << "type VEC"
        << "; x " << v.get_x()
        << "; y " << v.get_y()
        << "; num " << i
        << std::endl;
    }
    void draw(const std::vector<vec>& convex, int i) {
        return;
        for (int j = 0; j < convex.size(); ++j) {
            os << "type VEC"
            << "; x " << convex[j].get_x()
            << "; y " << convex[j].get_y()
            << "; num " << i
            << std::endl;
        }
    }
private:
    std::fstream fs;
    std::ostream &os;
    const Solver& slv;
};

class end{
public:
    end() = default;
};



void print(const frame& f) {
    for (int i = 0; i < agents.size(); ++i) {
        f.draw(agents[i]);
        std::cout << "Agent " << i << ": at " << currs[i] << std::endl;
    }
    for (int i = 0; i < currs.size(); ++i) {
        for (int j = i + 1; j < currs.size(); ++j) {
            if ((currs[i] - currs[j]).norm() < agents[i].get_r() + agents[j].get_r() - 4 * eps) {
                std::cerr << i << " and " << j << " collided" << std::endl;
                // assert(false);
            }
        }
    }
    std::cout << std::endl;
}