#include "algo.h"

bool Solver::reached(int i) {
    return ((currs[i] - goals[i]).norm() < eps);
}

bool Solver::finished() {
    for (int i = 0; i < agents.size(); ++i) {
        if (!reached(i)) {
            return false;
        }
    }
    return true;
}

const std::vector<agent>& Solver::get_agents() const {
    return agents;
}

const std::vector<vec>& Solver::get_currs() const {
    return currs;
}

const std::vector<vec>& Solver::get_goals() const {
    return goals;
}

const std::vector<vec>& Solver::get_v_curr() const {
    return v_curr;
}