#include <bitset>
#include <fstream>
#include <print>
#include <regex>
#include <string>

using namespace std;

enum class op { on, off, toggle };

struct instruction {
    op op;
    pair<size_t, size_t> tl;
    pair<size_t, size_t> br;
};

instruction parse(const string& str) {
    instruction ins;
    if (str.starts_with("turn off")) {
        ins.op = op::off;
    } else if (str.starts_with("turn on")) {
        ins.op = op::on;
    } else {
        ins.op = op::toggle;
    }

    regex pattern(R"((\d+),(\d+)\D+(\d+),(\d+))");
    smatch matches;
    regex_search(str, matches, pattern);
    ins.tl.first  = stol(matches[1].str());
    ins.tl.second = stol(matches[2].str());
    ins.br.first  = stol(matches[3].str());
    ins.br.second = stol(matches[4].str());
    return ins;
}

void config(array<bitset<1000>, 1000>& lights, const instruction& ins) {
    for (size_t i = ins.tl.first; i <= ins.br.first; ++i) {
        for (size_t j = ins.tl.second; j <= ins.br.second; ++j) {
            switch (ins.op) {
            case op::on:
                lights[i][j] = 1;
                break;
            case op::off:
                lights[i][j] = 0;
                break;
            case op::toggle:
                lights[i][j] = ~lights[i][j];
                break;
            }
        }
    }
}

void part1() {
    ifstream input("input/input06");
    array<bitset<1000>, 1000> lights;
    for (string line; getline(input, line);) {
        config(lights, parse(line));
    }
    size_t lit = 0;
    for (size_t i = 0; i < 1000; ++i) {
        for (size_t j = 0; j < 1000; ++j) {
            if (lights[i][j]) {
                ++lit;
            }
        }
    }
    println("{}", lit);
}

void part2() {
    ifstream input("input/input06");
    array<array<int, 1000>, 1000> lights;
    lights.fill({0});
    for (string line; getline(input, line);) {
        auto ins = parse(line);
        for (size_t i = ins.tl.first; i <= ins.br.first; ++i) {
            for (size_t j = ins.tl.second; j <= ins.br.second; ++j) {
                switch (ins.op) {
                case op::on:
                    lights[i][j] += 1;
                    break;
                case op::off:
                    lights[i][j] -= 1;
                    if (lights[i][j] < 0) {
                        lights[i][j] = 0;
                    }
                    break;
                case op::toggle:
                    lights[i][j] += 2;
                    break;
                }
            }
        }
    }

    int64_t brightness = 0;
    for (size_t i = 0; i < 1000; ++i) {
        for (size_t j = 0; j < 1000; ++j) {
            brightness += lights[i][j];
        }
    }
    println("{}", brightness);
}

int main() {
    part1();
    part2();
    return 0;
}
