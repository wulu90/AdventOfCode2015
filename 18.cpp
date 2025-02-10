#include <fstream>
#include <print>
#include <string>
#include <vector>

using namespace std;

int calc_nei_on(const vector<string>& light_map, size_t r, size_t c) {
    const static vector<pair<int, int>> neis{{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    int res = 0;
    for (auto& [dr, dc] : neis) {
        if (r + dr < 100 && c + dc < 100 && light_map[r + dr][c + dc] == '#') {
            ++res;
        }
    }
    return res;
}

void step(vector<string>& light_map) {
    auto tmp = light_map;
    for (size_t i = 0; i < 100; ++i) {
        for (size_t j = 0; j < 100; ++j) {
            auto num = calc_nei_on(light_map, i, j);
            if (light_map[i][j] == '#' && !(num == 2 || num == 3)) {
                tmp[i][j] = '.';
            }
            if (light_map[i][j] == '.' && num == 3) {
                tmp[i][j] = '#';
            }
        }
    }
    light_map = std::move(tmp);
}

int on_count(const vector<string>& light_map) {
    int res = 0;
    for (auto& str : light_map) {
        res += count(str.begin(), str.end(), '#');
    }
    return res;
}

void part1() {
    ifstream input("input/input18");
    vector<string> light_map;
    for (string line; getline(input, line);) {
        light_map.push_back(line);
    }

    for (int i = 0; i < 100; ++i) {
        step(light_map);
    }

    println("{}", on_count(light_map));
}

void step2(vector<string>& light_map) {
    auto tmp = light_map;
    for (size_t i = 0; i < 100; ++i) {
        for (size_t j = 0; j < 100; ++j) {
            auto num = calc_nei_on(light_map, i, j);
            if (light_map[i][j] == '#' && !(num == 2 || num == 3)) {
                tmp[i][j] = '.';
            }
            if (light_map[i][j] == '.' && num == 3) {
                tmp[i][j] = '#';
            }
        }
    }
    tmp[0][0]   = '#';
    tmp[0][99]  = '#';
    tmp[99][0]  = '#';
    tmp[99][99] = '#';
    light_map   = std::move(tmp);
}

void part2() {
    ifstream input("input/input18");
    vector<string> light_map;
    for (string line; getline(input, line);) {
        light_map.push_back(line);
    }

    light_map[0][0]   = '#';
    light_map[0][99]  = '#';
    light_map[99][0]  = '#';
    light_map[99][99] = '#';

    for (int i = 0; i < 100; ++i) {
        step2(light_map);
    }

    println("{}", on_count(light_map));
}

int main() {
    part1();
    part2();
    return 0;
}
