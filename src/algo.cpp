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

void Solver::print(const frame& f) {
    for (int i = 0; i < agents.size(); ++i) {
        f.draw(agents[i]);
        std::cout << "Agent " << i << ": at " << currs[i] << std::endl;
    }
    for (int i = 0; i < currs.size(); ++i) {
        for (int j = i + 1; j < currs.size(); ++j) {
            if ((currs[i] - currs[j]).norm() < agents[i].get_r() + agents[j].get_r() - 4 * eps) {
                std::cerr << i << " and " << j << " collided" << std::endl;
            }
        }
    }
    std::cout << std::endl;
}

std::istream& operator>>(std::istream& is, Solver& solver) {
    for (int i = 0; i < solver.agents.size(); ++i) {
        std::cin >> solver.agents[i];
        std::cin >> solver.goals[i];
        std::cin >> solver.currs[i];
        solver.v_curr[i] = vec(0, 0);
        std::cout << i << " " << solver.agents[i] << std::endl;
    }
    return is;
}