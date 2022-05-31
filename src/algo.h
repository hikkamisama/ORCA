#pragma once
#include "geometry/geom.h"
#include "agents.h"
#include "visualization/frame.h"
#include <vector>
#include <fstream>
#include <string>

class Solver {
public:
    Solver() = default;
    Solver(int n) {
        agents.resize(n);
        goals.resize(n);
        currs.resize(n);
        v_curr.resize(n);
    }
    Solver(const std::vector<agent>& agents, 
           const std::vector<vec>& currs,
           const std::vector<vec>& goals,
           const std::vector<vec> v_curr) : agents(agents), 
                                            currs(currs),
                                            goals(goals),
                                            v_curr(v_curr) {}
    Solver(const Solver& slv) {
        agents = slv.agents;
        currs = slv.currs;
        goals = slv.goals;
        v_curr = slv.v_curr;
    }
    bool reached(int i);
    bool finished();
    void print(const frame& f);
    const std::vector<agent>& get_agents() const;
    const std::vector<vec>& get_currs() const;
    const std::vector<vec>& get_goals() const;
    const std::vector<vec>& get_v_curr() const;
    friend std::istream& operator>>(std::istream& is, Solver& solver);
private:
    std::vector<agent> agents;
    std::vector<vec> currs;
    std::vector<vec> goals;
    std::vector<vec> v_curr;
};