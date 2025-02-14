#include <charconv>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <string_view>
#include <tuple>

using namespace std;

tuple<uint32_t, uint32_t, uint32_t> parse(string_view sv) {
    uint32_t l = 0;
    uint32_t w = 0;
    uint32_t h = 0;
    auto xpos  = sv.find('x');
    auto x1pos = sv.find('x', xpos + 1);
    from_chars(sv.data(), sv.data() + xpos, l);
    from_chars(sv.data() + xpos + 1, sv.data() + x1pos, w);
    from_chars(sv.data() + x1pos + 1, sv.data() + sv.size(), h);
    return {l, w, h};
}

uint32_t minside(const tuple<uint32_t, uint32_t, uint32_t>& cube) {
    auto [l, w, h] = cube;
    auto res       = min(l * w, w * h);
    res            = min(res, l * h);
    return res;
}

uint32_t surf_area(const tuple<uint32_t, uint32_t, uint32_t>& cube) {
    auto [l, w, h] = cube;
    return 2 * l * w + 2 * w * h + 2 * l * h;
}

uint32_t ribbon(const tuple<uint32_t, uint32_t, uint32_t>& cube) {
    auto [l, w, h] = cube;
    uint32_t res   = 0;
    res            = min(l + w, w + h);
    res            = min(res, h + l);
    return 2 * res;
}

uint32_t cubic_feet(const tuple<uint32_t, uint32_t, uint32_t>& cube) {
    auto [l, w, h] = cube;
    return l * w * h;
}

void part1() {
    uint32_t res = 0;
    ifstream input("input/input02");

    for (string str; getline(input, str);) {
        auto cube = parse(str);
        res += surf_area(cube) + minside(cube);
    }
    cout << res << endl;
}

void part2() {
    uint32_t res = 0;
    ifstream input("input/input02");

    for (string str; getline(input, str);) {
        auto cube = parse(str);
        res += ribbon(cube) + cubic_feet(cube);
    }
    cout << res << endl;
}

int main() {
    part1();
    part2();
}
