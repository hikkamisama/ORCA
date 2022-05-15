#include <cmath>
#include <vector>
#include <iostream>
#include <utility>
#include <cassert>
#include <fstream>

extern const double eps = 1e-4;
extern double tau = 5;
extern int all_time = 300;
extern double delta = 1;

#include "geom.h"
#include "agents.h"

std::vector<agent> agents;
std::vector<vec> currs;
std::vector<vec> goals;
std::vector<vec> v_curr;

struct end{
    end() = default;
};

struct frame {
    std::fstream fs;
    std::ostream &os;
    frame (const std::string& f_name) : fs(f_name, std::ios::out | std::ios::trunc), os(fs) {}
    void draw(const agent& a) const {
        os 
        << "type AGENT" 
        << "; num " << a.num 
        << "; x " << currs[a.num].x 
        << "; y " << currs[a.num].y 
        << "; r " << a.r 
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
        dd1 = dd1 + currs[i];
        dd2 = dd2 + currs[i];
        os << "type LINE" 
        << "; x1 " << dd1.x
        << "; y1 " << dd1.y
        << "; x2 " << dd2.x
        << "; y2 " << dd2.y
        << "; num " << i
        << std::endl;
    }
    void draw(const vec& v, int i) {
        os << "type VEC"
        << "; x " << v.x
        << "; y " << v.y
        << "; num " << i
        << std::endl;
    }
    void draw(const std::vector<vec>& convex, int i) {
        return;
        for (int j = 0; j < convex.size(); ++j) {
            os << "type VEC"
            << "; x " << convex[j].x
            << "; y " << convex[j].y
            << "; num " << i
            << std::endl;
        }
    }
};

void print(const frame& f) {
    for (int i = 0; i < agents.size(); ++i) {
        f.draw(agents[i]);
        std::cout << "Agent " << i << ": at " << currs[i] << std::endl;
    }
    for (int i = 0; i < currs.size(); ++i) {
        for (int j = i + 1; j < currs.size(); ++j) {
            if ((currs[i] - currs[j]).norm() < agents[i].r + agents[j].r - eps) {
                assert(false);
            }
        }
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
    frame f("test.txt");
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
        std::cout << i << " " << agents[i] << std::endl;
    }
    std::cout << std::endl;
    int curr_time = 0;
    while (curr_time < all_time && !finished()) {
        print(f);
        std::cout << "ITERATION №" << curr_time / 2 << std::endl;
        std::cout << std::endl;
        std::vector<vec> tmp_pos(n);
        std::vector<vec> new_vs(n);
        for (int i = 0; i < n; ++i) {
            std::vector<line> h_ps = poly_for_vmax(agents[i].v_max * delta, 8);
            for (int j = 0; j < n; ++j) {
                if (i == j) {
                    continue;
                }
                // struct vo i|j
                // struct half plane i|j
                auto [u, nu] = find_v_n(
                    find_cas(
                        circle((currs[j] - currs[i]) / tau,
                        (agents[j].r + agents[i].r) / tau),
                    vec(0, 0)),
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
                v_pref = normalize(v_ideal) * agents[i].v_max * delta;
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
