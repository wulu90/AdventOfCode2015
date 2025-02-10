#include <fstream>
#include <print>
#include <regex>
#include <string>

using namespace std;

struct ingredient {
    int capacity;
    int durability;
    int flavor;
    int texture;
    int claories;
};

ingredient parse(const string& str) {
    regex pattern{R"((-?\d+))"};
    ingredient ing;
    int i = 0;
    for (sregex_iterator it(str.begin(), str.end(), pattern); it != sregex_iterator(); ++it) {
        *(&ing.capacity + i++) = stoi(it->str());
    }
    return ing;
}

void part1() {
    ifstream input("input/input15");
    vector<ingredient> ing_vec;
    for (string line; getline(input, line);) {
        ing_vec.push_back(parse(line));
    }

    int max_score = 0;
    for (int i = 1; i <= 97; ++i) {
        for (int j = 1; j <= 98 - i; ++j) {
            for (int k = 1; k <= 99 - i - j; ++k) {
                auto m  = 100 - i - j - k;
                auto ca = i * ing_vec[0].capacity + j * ing_vec[1].capacity + k * ing_vec[2].capacity + m * ing_vec[3].capacity;
                auto du = i * ing_vec[0].durability + j * ing_vec[1].durability + k * ing_vec[2].durability + m * ing_vec[3].durability;
                auto fl = i * ing_vec[0].flavor + j * ing_vec[1].flavor + k * ing_vec[2].flavor + m * ing_vec[3].flavor;
                auto te = i * ing_vec[0].texture + j * ing_vec[1].texture + k * ing_vec[2].texture + m * ing_vec[3].texture;

                ca = ca > 0 ? ca : 0;
                du = du > 0 ? du : 0;
                fl = fl > 0 ? fl : 0;
                te = te > 0 ? te : 0;

                int score = ca * du * fl * te;

                max_score = max(max_score, score);
            }
        }
    }

    println("{}", max_score);
}

void part2() {
    ifstream input("input/input15");
    vector<ingredient> ing_vec;
    for (string line; getline(input, line);) {
        ing_vec.push_back(parse(line));
    }

    int max_score = 0;
    for (int i = 1; i <= 97; ++i) {
        for (int j = 1; j <= 98 - i; ++j) {
            for (int k = 1; k <= 99 - i - j; ++k) {
                auto m  = 100 - i - j - k;
                auto ca = i * ing_vec[0].capacity + j * ing_vec[1].capacity + k * ing_vec[2].capacity + m * ing_vec[3].capacity;
                auto du = i * ing_vec[0].durability + j * ing_vec[1].durability + k * ing_vec[2].durability + m * ing_vec[3].durability;
                auto fl = i * ing_vec[0].flavor + j * ing_vec[1].flavor + k * ing_vec[2].flavor + m * ing_vec[3].flavor;
                auto te = i * ing_vec[0].texture + j * ing_vec[1].texture + k * ing_vec[2].texture + m * ing_vec[3].texture;
                auto cl = i * ing_vec[0].claories + j * ing_vec[1].claories + k * ing_vec[2].claories + m * ing_vec[3].claories;

                if (cl != 500) {
                    continue;
                }

                ca = ca > 0 ? ca : 0;
                du = du > 0 ? du : 0;
                fl = fl > 0 ? fl : 0;
                te = te > 0 ? te : 0;

                int score = ca * du * fl * te;

                max_score = max(max_score, score);
            }
        }
    }

    println("{}", max_score);
}

int main() {
    part1();
    part2();
    return 0;
}
