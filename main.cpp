#include <cmath>
#include <vector>
#include <iostream>
#include <utility>

extern const double eps = 1e-4;
extern double tau = 2;
extern int all_time = 10000;

#include "geom.h"
#include "agents.h"

std::vector<agent> agents;
std::vector<vec> currs;
std::vector<vec> goals;
std::vector<vec> v_curr;

void print() {
    for (int i = 0; i < agents.size(); ++i) {
        std::cout << "Agent " << i << ": at " << currs[i] << std::endl;
        std::cerr << "Circle " << currs[i].x << " " << currs[i].y << " " << agents[i].r << std::endl;
    }
    std::cout << std::endl;
}

bool reached(int i) {
    return ((currs[i] - goals[i]).norm() < eps);
}

bool finished() {
    for (int i = 0; i < agents.size(); ++i) {
        if (!reached(i)) {
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    std::cin >> n;
    agents.resize(n);
    goals.resize(n);
    currs.resize(n);
    v_curr.resize(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> agents[i];
        std::cin >> goals[i];
        std::cin >> currs[i];
        v_curr[i] = vec(0, 0);
        std::cout << agents[i] << "; " << reached(i) << " " << finished() << std::endl;
    }
    int curr_time = 0;
    while (curr_time < all_time && !finished()) {
        std::vector<vec> tmp_pos(n);
        std::vector<vec> new_vs(n);
        for (int i = 0; i < n; ++i) {
            std::vector<line> h_ps = poly_for_vmax(agents[i].v_max, 8);
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                // struct vo i|j
                // struct half plane i|j
                auto [u, n] = find_v_n(
                    find_cas(
                        circle((currs[j] - currs[i]) / tau,
                        (agents[j].r + agents[i].r) / tau),
                    vec(0, 0)),
                    v_curr[i] - v_curr[j]
                );
                line h_p = struct_half_plane(v_curr[i], u, n);
                std::cout << "ORCA" << i << "|" << j << ": " << h_p << std::endl;
                h_ps.push_back(h_p);
            }
            // intersect all half planes
            // find distance to intersection
            vec v_ideal = vec(currs[i], goals[i]);
            vec v_pref;
            if (v_ideal.norm() < eps) {
                v_pref = vec(0, 0);
            } else {
                v_pref = normalize(v_ideal) * agents[i].v_max * tau;
            }
            std::cout << "Agent " << i << " wants: " << v_ideal << " " << v_pref << "\n";
            if (v_pref.norm() >= v_ideal.norm()) {
                v_pref = v_ideal;
            }
            bool flag = false;
            for (int k = 0; k < h_ps.size(); ++k) {
                if (h_ps[k].into(v_pref) < -eps) {
                    flag = true;
                    break;
                }
            }
            vec v_new;
            if (flag) {
                v_new = solve(convex_hull(h_ps), v_pref);
            } else {
                v_new = v_pref;
            }
            std::cout << "Agent " << i << " gets: " << v_new << "\n";
            new_vs[i] = v_new;
            tmp_pos[i] = currs[i] + v_new;
        }
        // move agent to new position
        //update currs, v_curr
        currs = tmp_pos;
        v_curr = new_vs;
        curr_time += 2;
        print();
    }
    std::cout << curr_time << " " << finished() << std::endl;
    return 0;
}
