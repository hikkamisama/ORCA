#pragma once
#include <fstream>
#include <string>
#include <vector>
#include "../agents.h"
#include "../geometry/geom.h"
#include "../algo.h"
#include "../const.h"

class frame {
public:
    frame (const std::string& f_name, const Solver& slv) : fs(f_name, std::ios::out | std::ios::trunc), os(fs), slv(slv) {}
    void draw(const agent& a) const;
    void draw(const end& e) const {
        os << "type END" << std::endl;
    }
    void draw(const line& l, int i);
    void draw(const vec& v, int i);
    void draw(const std::vector<vec>& convex, int i);

private:
    std::fstream fs;
    std::ostream &os;
    const Solver& slv;
};

class end{
public:
    end() = default;
};