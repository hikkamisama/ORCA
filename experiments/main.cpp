#include <cmath>
#include <vector>
#include <iostream>
#include <utility>
#include <cassert>

#include "../src/algo.h"

int main() {
    int n;
    std::cin >> n;
    Solver solver(n);
    frame f("test.txt", solver);
    std::cin >> solver;
    std::cout << std::endl;
    int curr_time = 0;
    while (curr_time < all_time && !solver.finished()) {
        solver.print(f);
        std::cout << "ITERATION №" << curr_time / 2 << std::endl;
        std::cout << std::endl;
        std::vector<vec> tmp_pos(n);
        std::vector<vec> new_vs(n);
        for (int i = 0; i < n; ++i) {
            std::vector<line> h_ps = poly_for_vmax(agents[i].get_v_max() * delta, 8);
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                // struct vo i|j
                // struct half plane i|j
                circle vo_base((currs[j] - currs[i]) / tau,
                        (agents[j].get_r() + agents[i].get_r()) / tau);
                auto [u, nu] = find_v_n(
                    find_cas(vo_base, vec(0, 0)), 
                    v_curr[i] - v_curr[j]
                );
                line h_p = struct_half_plane(v_curr[i], u, nu);
                f.draw(h_p, i);
                std::cout << "ORCA " << i << "|" << j << ": " << h_p << std::endl;
                h_ps.push_back(h_p);
            }
            std::cout << std::endl;
            // intersect all half planes
            // find distance to intersection
            vec v_ideal = vec(currs[i], goals[i]);
            vec v_pref;
            if (v_ideal.norm() < eps) {
                v_pref = vec(0, 0);
            } else {
                v_pref = normalize(v_ideal) * agents[i].get_v_max() * delta;
            }
            std::cout << "Agent " << i << " wants: " << v_pref << "\n";
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
            std::vector<vec> c_h = convex_hull(h_ps);
            vec v_new;
            if (flag) {
                v_new = solve(c_h, v_pref);
            } else {
                v_new = v_pref;
            }
            for (int j = 0; j < c_h.size(); ++j) {
                c_h[j] = c_h[j] + currs[i];
            }
            f.draw(c_h, i);
            std::cout << "Agent " << i << " gets: " << v_new << std::endl;
            std::cout << std::endl;
            new_vs[i] = v_new;
            tmp_pos[i] = currs[i] + v_new;
        }
        // move agent to new position
        //update currs, v_curr
        currs = tmp_pos;
        v_curr = new_vs;
        curr_time += delta;
        f.draw(end());
    }
    std::cout << "Finished at: " << curr_time << std::endl;
    return 0;
}
