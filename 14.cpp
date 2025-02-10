#include <fstream>
#include <map>
#include <print>
#include <ranges>
#include <string>
#include <vector>

using namespace std;

struct reindeer {
    string name;
    int speed;
    int fly;
    int rest;
};

reindeer parse(const string& str) {
    reindeer rd;
    auto spv = str | views::split(" "sv);
    rd.name  = string_view{*spv.begin()};

    auto it = next(spv.begin(), 3);
    from_chars((*it).data(), (*it).data() + (*it).size(), rd.speed);

    it = next(spv.begin(), 6);
    from_chars((*it).data(), (*it).data() + (*it).size(), rd.fly);

    it = next(spv.begin(), 13);
    from_chars((*it).data(), (*it).data() + (*it).size(), rd.rest);

    return rd;
}

void part1() {
    ifstream input("input/input14");
    vector<reindeer> deer_vec;
    for (string line; getline(input, line);) {
        deer_vec.push_back(parse(line));
    }

    const static int time = 2503;

    vector<int> dist_vec;
    for (auto& rd : deer_vec) {
        int fly_num = time / (rd.fly + rd.rest);
        int m_t     = time % (rd.fly + rd.rest);
        m_t         = m_t >= rd.fly ? rd.fly : m_t;
        dist_vec.push_back(fly_num * rd.speed * rd.fly + rd.speed * m_t);
    }

    println("{}", *max_element(dist_vec.begin(), dist_vec.end()));
}

void part2() {
    ifstream input("input/input14");
    vector<reindeer> deer_vec;
    for (string line; getline(input, line);) {
        deer_vec.push_back(parse(line));
    }

    const static int time = 2503;

    vector<int> deer_points(deer_vec.size(), 0);
    for (int t = 1; t <= time; ++t) {
        multimap<int, size_t> dist_inx;
        for (size_t i = 0; i < deer_vec.size(); ++i) {
            auto& rd    = deer_vec[i];
            int fly_num = t / (rd.fly + rd.rest);
            int m_t     = t % (rd.fly + rd.rest);
            m_t         = m_t >= rd.fly ? rd.fly : m_t;
            dist_inx.insert({fly_num * rd.speed * rd.fly + rd.speed * m_t, i});
        }

        auto max_dist = dist_inx.rbegin()->first;
        auto [b, e]   = dist_inx.equal_range(max_dist);
        for (auto it = b; it != e; ++it) {
            ++deer_points[it->second];
        }
    }

    println("{}", *max_element(deer_points.begin(), deer_points.end()));
}

int main() {
    part1();
    part2();
    return 0;
}
