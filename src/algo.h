#pragma once
#include "geometry/geom.h"
#include "agents.h"
#include <vector>
#include <fstream>
#include <string>

class Solver {
public:
    Solver() = default;
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
    const std::vector<agent>& get_agents() const;
    const std::vector<vec>& get_currs() const;
    const std::vector<vec>& get_goals() const;
    const std::vector<vec>& get_v_curr() const;
private:
    std::vector<agent> agents;
    std::vector<vec> currs;
    std::vector<vec> goals;
    std::vector<vec> v_curr;
};